## Configuration file to control individual members of an ensemble.
## Defaults are taken from ecf/config_exp.h.
## All modifications should be done in the perl hash %env below.
## The keys of %env are environment variable names, e.g. "ANASURF", "ANAATMO", etc.
## The values ($env{var}) can be given in four different ways:
## 1. A hash reference, i.e., 'VAR' => { m1 => 'val1', m2 => 'val2', ... }
##    m1, m2, etc. are numbers (members listed in $ENSMSEL in config_exp.h, in any order).
## 2. An array reference, i.e., 'VAR' => [ 'val1','val2',... ]
##    Value order is the same as member order in $ENSMSEL.
##    An array that is too short is recycled from the beginning,
##    e.g. 'PHYSICS' => [ 'arome','alaro' ] would mean that every second member
##    run with arome physics and the others with alaro.
## 3. A scalar, i.e., 'VAR' => 'string'. This string is subject to variable substitution,
##    i.e., any appearance of @EEE@ is substituted with the corresponding 3-digit member
##    number.
## 4. A code reference, i.e., 'VAR' => sub { perl code; return something member specific; }
##    This subroutine is given the same arguments as the invoking &Env('VAR',args) call
##    (except 'VAR' of course) and should return a string which will then be the return
##    value of this &Env call.

%env = (
   'ANAATMO'  => { 0 => '3DVAR' },
   'LSMIXBC'  => { 0 => 'yes' },
   'ANASURF'  => { 0 => 'CANARI_OI_MAIN' },
   'ENSCTL' => [ '000' ],
   'PERTATMO' => { 0 => 'none' },
   'PERTSURF' => { 0 => 'none' },
   'SPP'      => { 0 => 'no' },
   'OBSMONITOR' => { 0 => 'obstat' },
   #'PHYSICS' => [ "arome", "alaro" ],  # Use this for multi-model (in LETKF, HarmonEPS, ...).

# SLAFLAG: Forecast length to pick your perturbation end point from
# SLAFDIFF: Hours difference to pick your perturbation start point from
# SLAFLAG=24, SLAFDIFF=6 will use +24 - +18
# SLAFDIFF=SLAFLAG will retain the original SLAF construction
# SLAFK should be tuned so that all members have the same perturbation size
#
# If SCALE_PERT = yes (in ecf/config_exp.h) then the value of SLAFK is not used.
# Instead SLAFK is scaled according to a reference level of total energy (EREF)
# which is tunable.
# The sign of SLAFK is still used to determine whether the perturbation should
# be added or subtracted from the control.
#
# If SLAFLAG > 48, the perturbation will use a SLAFLAG old forecast with forecast
# length SLAFDIFF, i.e. the perturbation will not be based on "the error of the day".
# If SLAFLAG < 0, a random date will be chosen ("random field perturbation").
# The value of SLAFLAG will be used as seed for the random number generator,
# so same value will give same date (useful if you want to ensure symmetric (+/-) perturbations).
#
   'ENSBDMBR' => [ -1 ],
   'SLAFLAG'  => [    0,    6,     6,    12,    12,  18,     18,   24,    24,    30,    30],
   'SLAFDIFF' => [    0,    6,     6,     6,     6,    6,     6,    6,     6,     6,     6],
# When using ECMWF ENS the members should be defined
   # 'ENSBDMBR' => [ 0, 1..10 ],

### Normally NO NEED to change the settings below
   'ARCHIVE' => '${ARCHIVE}/mbr@EEE@/',
   'EXTRARCH' => '${EXTRARCH}/${OBSMON_EXP}/mbr@EEE@/',
   ##'CLIMDIR' => '$CLIMDIR/mbr@EEE@',
   'OBDIR'   => '$OBDIR/mbr@EEE@',
   'VFLDEXP' => '${EXP}mbr@EEE@',
   'BDDIR'   => sub { my $mbr = shift;
		       return '$BDDIR/mbr'.sprintf('%03d',&Env('ENSBDMBR',$mbr));
                  },
   'FCINT' => sub { my $mbr = shift;
		    my @cycles = &expand_list(&Env('HH_LIST',$mbr),"%d");
		    return $cycles[0] + 24 - $cycles[-1];
                  },
   'DTGBEG' => sub { my $mbr = shift;
		     my $dtgbeg = $ENV{DTGBEG};
		     my $hhbeg = substr($dtgbeg,8,2);
		     my @cycles = &expand_list(&Env('HH_LIST',$mbr),"%d");
		     return $dtgbeg unless(@cycles);
		     push(@cycles,$cycles[0]+24);
		     for (my $i=0; $i<=$#cycles; $i++) {
			my $hh = $cycles[$i];
			if ($hh == $hhbeg) {
			   return $dtgbeg;
			} elsif ( $hh > $hhbeg ) {
			   if ( $hh < 24 ) {
			      return substr($dtgbeg,0,8) . sprintf "%02d", $hh;
			   } else {
			      my $diff = $hh - $hhbeg;
			      chomp(my $dtg=qx(mandtg $dtgbeg + $diff));
			      return $dtg;
			   }
			}
		     }
                   }
    );


## ============================================================================
## No need to change the subroutines below unless you know what you are doing

sub Env {
# Usage: Env('var','mbr'[,'test'])
# If 'mbr' is a number or 'min' or 'max', then 'test' is ignored (should be empty).
# If 'mbr' is 'any' or 'all', 'test' should be a string.

   my ($var,$mbr,$test) = @_;
   die "Nonexistent environment variable '$var' in &Env\n"
      unless (exists $ENV{$var});
   die "Illegal second argument in &Env('$var','$mbr')\n"
       unless ($mbr =~ /^([+-]?\d+|all|any|min|max|union)$/);
   unless ( $mbr =~ /[a-z,A-Z]{1,}/ ) {
    return $ENV{$var} if ($mbr == -1);
   }
   if (defined($DEBUG)){
    my $dbg = ($DEBUG > 2);
   } else { $dbg = 0 ; }

   my %inires = ( 'all'=>1, 'min'=>2147483647, 'max'=>-2147483647 );
   my $result = ( exists $inires{$mbr} ? $inires{$mbr} : 0 );
   my %union = ();
   my @elist = split(':',$ENV{ENSMSELX});
   return $ENV{$var} unless (@elist);
   for (my $i=0; $i<=$#elist; $i++) {
      my $eee = $elist[$i];
      my $e = sprintf("%d",$eee);
      my $val = $ENV{$var};
      if ( exists $env{$var} ) {
	 if ( ref($env{$var}) eq 'HASH' ) {
	    if ( exists $env{$var}{$e} ) {
	       $val = $env{$var}{$e};
	    } elsif ( exists $env{$var}{$eee} ) {
	       $val = $env{$var}{$eee};
	    }
	 } elsif ( ref($env{$var}) eq 'ARRAY' ) {
	    my $alen = scalar(@{$env{$var}});
	    my $aix = $i % $alen;   # cycle array if too short
	    $val = $env{$var}[$aix];
	 } elsif ( ref($env{$var}) eq 'CODE' ) {
	    my $cref = $env{$var};
	    $val = $cref->($mbr,$test,@_);
	 } else {
	    $val = $env{$var};
	    $val =~ s|\@EEE\@|$eee|g;
	    $val =~ s|/mbr\-1||g;
	 }
      } else {
	 return $val unless ($mbr eq 'any' or $mbr eq 'all'
			     or $mbr eq 'union');
      }
      if ($mbr eq 'any') {
	 $result |= ($val eq $test);
      } elsif ($mbr eq 'all') {
	 $result &= ($val eq $test);
      } elsif ($mbr eq 'min') {
	 $result = $val if ($val < $result);
      } elsif ($mbr eq 'max') {
	 $result = $val if ($val > $result);
      } elsif ($mbr eq 'union') {
	 for ( &expand_list($val,"%d") ) { $union{$_} = 1; }
      } elsif ($mbr == $e) {
	 print DEBUG "Env($var,$mbr) -> $val\n" if $dbg;
	 return $val;
      }
   }
   if ( $mbr eq 'union' ) {
      $result = join(' ', sort { $a <=> $b } keys %union);
   }
   print DEBUG "Env($var,$mbr,$test) -> $result\n" if $dbg;
   return $result;
}

sub expand_list {
   my $value = shift;
   my $format = shift || "%03d";
   my $sep = shift || ':';
   # remove duplicates, and convert to numerically sorted array
   my %items = ();
   for my $item ( split(',',$value) ) {
      if ( $item =~ /^(\d+)\-(\d+)$/ ) {
	 for my $mbr ( $1 .. $2 ) { $items{$mbr} = 1; }
      } elsif ( $item =~ /^(\d+)\-(\d+)\:(\d+)$/ ) {
         for (my $mbr=$1; $mbr<=$2; $mbr+=$3) { $items{$mbr} = 1; }
      } elsif ( $item =~ /^(\d+)$/ ) {
         $items{$1} = 1;
      } else {
         die "$0: '$value' is in error: bad syntax: '$item'\n";
      }
   }
   my @list = ();
   for my $item ( sort { $a <=> $b } keys %items ) {
      push @list, sprintf($format,$item);
   }
   if ( @list ) {
      return wantarray ? @list : join($sep,@list);
   } else {
      return '';
   }
}

1;
