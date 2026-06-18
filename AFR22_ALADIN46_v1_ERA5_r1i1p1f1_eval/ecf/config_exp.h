# -*- shell-script -*-
# HARMONIE experiment configuration file
#
# Please read the documentation on https://hirlam.org/trac/wiki/HarmonieSystemDocumentation first
#
# NB! All combinations may not be valid or well tested
#
# **** Build and bin paths ****
# Definitions about Build, should fit with hm_rev
BUILD=${BUILD-yes}                            # Turn on or off the compilation and binary build ( yes|no)
BINDIR=${BINDIR-$HM_DATA/bin}                 # Binary directory
BUILD_WITH=${BUILD_WITH-makeup}               # Build system to use (makeup|cmake)
CMAKE_BUILD_TYPE=Release                      # CMake build type (Debug|Release)

COMPILE_ENKF=${COMPILE_ENKF-"no"}             # Compile LETKF code (yes|no)
SURFEX_OFFLINE_BINARIES="no"                  # Switch to compile and use offline SURFEX binaries

# **** Misc, defined first because it's used later ****

CNMEXP=HARM                             # Four character experiment identifier
WRK=$HM_DATA/$CYCLEDIR                  # Work directory

# **** Paths to archive ****
# We need to define ARCHIVE early since it might be used further down


ARCHIVE_ROOT=$HM_DATA/archive           # Archive root directory
ECFSLOC=ec                              # Archiving site at ECMWF-ECFS: "ec" or ECFS-TMP "ectmp"
ECFSGROUP=accord                        # Group in which to chgrp the ECMWF archive, "default" or "accord"
EXTRARCH=$ARCHIVE_ROOT/extract          # Archive for fld/obs-extractions


# **** Running mode ****
RUNNING_MODE=research                   # Research or operational mode (research|operational)
                                        # operational implies that the suite will continue even if e.g.
                                        # observations are missing or assimilation fails

SIMULATION_TYPE=climate                 # Type of simulation (nwp|climate)
FP_PRECISION=double                     # double|single|dual  (if makeup config file updated)
[ "$FP_PRECISION" = "dual" ] && BINDIR=$HM_DATA/bin/R64

# **** Model geometry ****
DOMAIN=AFR22                            # See definitions in scr/Harmonie_domains.pm
TOPO_SOURCE=gmted2010                   # Input source for orography. Available are (glo90|gmted2010|gtopo30)
                                        # For glo90, set HM_CLDATA=/hpcperm/ic0/pgd/uwc in Env_system
GRID_TYPE=LINEAR                        # Type of grid (LINEAR|QUADRATIC|CUBIC)
VLEV=65                                 # Vertical level definition name
                                        # HIRLAM_60, MF_60,HIRLAM_40, or
                                        # BOUNDARIES = same number of levs as on boundary file.
                                        # See the other choices from scr/Vertical_levels.pl

# **** High level forecast options ****
DYNAMICS="h"                           # Hydrostatic or non-hydrostatic dynamics (h|nh)
VERT_DISC=vfd                           # Discretization in the vertical (vfd,vfe)
                                        # Note that vfe does not yet work in non-hydrostatic mode
PHYSICS="aladin"                         # Main model physics flag (arome|alaro)
DFI="none"                              # Digital filter initialization (idfi|fdfi|none)
                                        # idfi : Incremental dfi
                                        # fdfi : Full dfi
                                        # none : No initialization (AROME default case)
LSPBDC=no                               # Spectral upper boundary contions option (no|yes)
LGRADSP=yes                             # Apply Wedi/Hortal vorticity dealiasing (yes|no)
LUNBC=yes                               # Apply upper nested boundary condition (yes|no)

# Highlighted physics switches
PYSURFEX=""
export PYSURFEX_INSTALL_DIR="$HM_DATA/install/pysurfex"
export PATH="$PYSURFEX_INSTALL_DIR/bin:$PATH"
export PYTHONPATH="$PYSURFEX_INSTALL_DIR:$PYTHONPATH"

CISBA="DIF"                             # Type of ISBA scheme in SURFEX. Options: "3-L"|"2-L"|"DIF"
CSNOW="3-L"                             # Type of snow scheme in SURFEX. Options: "D95" and "3-L"
CROUGH="NONE"                           # SSO scheme used in SURFEX "NONE"|"Z01D"|"BE04"|"OROT"
SURFEX_SEA_ICE="sice"                   # Treatment of sea ice in surfex (none|sice)
MODIFY_LAKES=F                          # Use Vanern/VAttern as Sea, requires new climate files
SURFEX_LAKES="FLAKE"                    # Treatment of lakes in surfex (WATFLX|FLAKE)
MASS_FLUX_SCHEME=edmfm                  # Version of EDMF scheme (edkf|edmfm)
                                        # Only applicable if PHYSICS=arome
                                        # edkf is the AROME-MF version
                                        # edmfm is the KNMI implementation of Eddy Diffusivity Mass Flux scheme for Meso-scale
STATNW="yes"                            # Switch for new set up cloud scheme (yes|no)
HARATU="no"                             # Switch for HARATU turbulence scheme (yes|no)
HGT_QS="no"                             # Switch for height dependent VQSIGSAT (yes|no)
WINDFARM="no"                           # Switch for Fitch et al. (2012) wind turbine parametrization (yes|no)
ALARO_VERSION=0                         # Alaro version (1|0)
NPATCH=3                                # Number of patches over land in SURFEX (see also LISBA_CANOPY)
LISBA_CANOPY=".FALSE."                  # Activates surface boundary multi layer scheme over land in SURFEX (must be .FALSE. for NPATCH>1)
XRIMAX=0.2                              # Maximum allowed Richardson number in the surface layer (cy40h default was 0.0)

# Rsmin settings
RSMIN_DECIDUOUS_FACTOR=1.13             # Multiply forest and trees default RSMIN values with this factor
RSMIN_CONIFEROUS_FACTOR=1.44            # Multiply coniferous trees default RSMIN values with this factor
RSMIN_C3_FACTOR=1.5                     # Multiply C3 crops and grass default RSMIN values with this factor
RSMIN_C4_FACTOR=1.13                    # Multiply C4 crops default RSMIN values with this factor


# Coefficients for soil, vegetation and snow heat capacities
XCGMAX=2.0E-5				# Maximum value for soil heat capacity; default=2.0E-5
CV_LOWVEG=2.0E-5			# Value for low vegetation heat capacity; default=2.0E-5
CV_HIGHVEG=1.0E-5			# Value for high vegetation heat capacity; default=1.0E-5
XCSMAX=2.0E-4				# Maximum value for snow heat capacity; default=2.0E-4

# Coefficients for vegetation roughness length for grass and crops
XALLEN_TERM=2.5                         # crops: zallen=exp((LAI-XALLEN_TERM)/1.3); default=3.5
XGRASS_H_DNM=3.0                        # grass: z0=0.13*LAI/XGRASS_H_DNM; default=6.0

# Coefficients for exchange coefficients CD and CH in stable case over nature tile
XCD_COEFF1=10.0				# ZFM = 1. + XCD_COEFF1*PRI(JJ) / SQRT( 1.+XCD_COEFF2*PRI(JJ) )
XCD_COEFF2=5.0                          # ZFM = 1. + XCD_COEFF1*PRI(JJ) / SQRT( 1.+XCD_COEFF2*PRI(JJ) )
XCH_COEFF1=15.0                         # PAC(JJ) = ZCDN(JJ)*ZVMOD(JJ)/(1.+XCH_COEFF1*ZSTA(JJ)*ZDI(JJ)

# File with coordinates and properties of wind turbines
WINDFARM_COORDS_FILE=$WINDFARM_DATA_PATH/wind_turbine_coordinates_${DOMAIN}_@YYYY@.tab

# **** Radiation choices within HARMONIE-AROME  ****

RADSCHEME=RAYFM                         # RAYFM for IFS (default) | RAY for ACRANEB2 from ALARO - note that ACRANEB2 has not been fully tested in HARMONIE-AROME

# **** Assimilation ****
LOOPS="no"
ANAATMO=none                            # Atmospheric analysis (3DVAR|4DVAR|blending|none)
IAUVAR=no                               # READ THE DOCUMENTATION BEFORE TURNING THIS ON!

LVARCONS='.FALSE.'                      # apply VC to analysis increments for a better balanced initital state
AUGMENT_CV=NO                           # Augment control vector (NO|ENS)
Q_IN_SP=no                              # Transform humidity to spectral space for minimization using AROME(no|yes)    
ANASURF=none                            # Surface analysis (CANARI_OI_MAIN|OI|CANARI_EKF_SURFEX|EKF|fgcopy|none)
                                        # CANARI_OI_MAIN    : CANARI + SURFEX OI
                                        # CANARI_EKF_SURFEX : CANARI + SURFEX EKF ( experimental )
                                        # OI                : TITAN + gridPP + SODA
                                        # EKF               : TITAN + gridPP + SODA
                                        # fgcopy            : Copy initial from previous cycle
                                        # none              : No surface assimilation, cold start each cycle
ANASURF_OI_COEFF="POLYNOMES_ISBA_MF6"   # Specify use of OI coefficients file (POLYNOMES_ISBA|POLYNOMES_ISBA_MF6)
                                        # POLYNOMES_ISBA_MF6 means 6 times smaller coefficients for WG2 increments
ANASURF_MODE="before"                   # When ANASURF should be done
                                        # before            : Before ANAATMO
                                        # after             : After ANAATMO
                                        # both              : Before and after ANAATMO (Only for ANAATMO=4DVAR)

LPATCH1=FALSE                           # snow fg from grid-point average (FALSE) or from patch 1 (TRUE) 

# Obs settings
COBS_M="T2M,HU2M,SWE"                   # Observation types
NNCO="1,1,1"                            # Active observations. EKF neglects SWE
export COBS_M NNCV NNCO

# EKF settings
CVAR_M="WG6,WG5,WG4,WG3,WG2,TG2,TG1"          # EKF control variables
NNCV="1,1,1,1,1,1,1"                          # Active EKF control variables.
XSIGMA_M="0.2, 0.2, 0.2, 0.25, 0.25,2,2"      # Model error
XERROBS_M="1,0.1,-99.9"                       # Observation error (SWE not used)
LLINCHECK=TRUE  #TRUE|FALSE                   # Linearity check of Jacobians
XALPHA=0.2                                    # Alpha in linearity check
XTPRT_M="0.001,0.001,0.001,0.001,0.001,0.0001,0.0001" # Perturbation magnitudes for control variables
export CVAR_M NNCV XSIGMA_M XERROBS_M LLINCHECK XALPHA XTPRT_M

CFORCING_FILETYPE="NETCDF"              # Offline surfex forcing format (NETCDF/ASCII)

LSMIXBC=yes                             # Spectral mixing of LBC0 file before assimilation
JB_INTERPOL=no                          # Interpolation of structure functions from a pre-defined domain to your domain
LBIGEZ_MINIM="no"                       # Use a large E-zone in the minimization (no|yes)
LBGE_BIGEZ="no"                         # Derive background error statistics for domain with large extension zone
PROLOG_INT_METHOD=fullpos               # Use gl or fullpos to changes resolution (fullpos|gl)
JB_REF_DOMAIN=DKCOEXP                   # Reference domain used for interpolation of structure functions.
                                        # Note that the vertical level definition has to be the same

# **** Observations ****
OBDIR=$HM_DATA/observations             # Observation file directory
SINGLEOBS=no                            # Run single obs experiment with observation created by scr/Create_single_obs (no|yes)

USE_MSG=no                              # Use MSG data for adjustment of inital profiles, EXPERIMENTAL! (no|yes), expects MSGcloudYYYYMMDDHH.grib in $OBDIR

USE_DFS=no                              # Produce Degrees of Freedom for Signal diagnostics (yes|no)

# **** 4DVAR settings ****
NOUTERLOOP=2                            # 4DVAR outer loops, need to be 1 at present
ILRES=6,3                               # Resolution (in parts of full) of outer loops
TSTEP4D=300,150                         # Timestep length (seconds) of outer loops TL+AD
TSTEPTRAJ=300,300                       # How often the model state is saved for linearization
NITER4D=10,15                           # Maximum number of inner loop iterations in 4D-Var outer loops
NSIMU4D=15,20                           # Maximum number of cost function simulations in 4D-Var outer loops
TL_TEST=yes                             # Only active for playfile tlad_tests
AD_TEST=yes                             # Only active for playfile tlad_tests
CH_RES_SPEC=yes                         # yes => change of resolution of the increment spectrally; no => by FULLPOS
FORCE1=no                               # yes => tendency increment; no => analysis increment in loop 1
FORCE2=no                               # yes => tendency increment; no => analysis increment in loop 2
MINPHYSICS="arome"

# **** LETKF ****
HYBRID=no                               # Dummy here, needed by CheckOptions.pl
LETKF_3DSCREEN="yes"                    # Dummy here, needed by include.ass
LETKF_LAG="no"
if [ "$ANAATMO" = "LETKF" ]; then
  ANASURF_MODE="after"                  # Highly recommended so far. Better scores than "before". This needs research...
  ADDITIVE_INFLATION="TRUE"             # Default option... So far better scores
  HYBRID=no                             # (yes|no) to allow hybrid 3DVAR/LETKF analysis. Gain recentred ensemble method
  KHYBRID=0.5                           # Weight factor for hybrid analysis (only valid if HYBRID=yes)
  LETKF_3DSCREEN="yes"                  # (yes|no) to compute H(x) in Screening (no integration along analysis window, much cheaper computing)
  LSMIXBC="no"                          # LSMIXBC is yes only for the control member (see harmonie.pm). LSMIX has very positive impact
  CH_RES_SPEC=no                        # This is for when using LETKF_3DSCREEN="no"
  NOUTERLOOP=1                          # This is for when using LETKF_3DSCREEN="no"
  AI_ARCH=$HM_DATA/add_infl             # archive directory for additive inflation. Useful if one reruns an experiment not to use MARS again
  LETKF_LAG="no"                        # (yes|no) to double ensemble size by using ENSSIZE members from previous run
  LETKF_CONTROL="yes"                   # (yes|no) to use background from control member to construct LETKF analysis (KENDA approximation)
fi

# **** DFI setting ****
TAUS=5400                               # cut-off frequency in second
TSPAN=5400                              # 7200s or 5400s

# **** Nesting ****
HOST_MODEL="ifs"                        # Host model (ifs|hir|ald|ala|aro|racmo)
                                        # ifs  : ecmwf data
                                        # hir  : hirlam data
                                        # ald  : Output from aladin physics
                                        # ala  : Output from alaro physics
                                        # aro  : Output from arome physics
                                        # racmo: RACMO2 data

HOST_SURFEX="no"                        # yes if the host model is run with SURFEX
NBDMAX=12                               # Number of parallel interpolation tasks
MULTITASK=no                            # Submit jobs through the multi-task script
                                        #  yes|no, or list among: lbc,listen,obsmon,fldextr,femars,pertdia
BDLIB=ECMWF                             # Boundary experiment, set:
                                        # ECMWF to use MARS data
                                        # RCRa  to use RCRa data from ECFS
                                        # Other HARMONIE/HIRLAM experiment

BDDIR=$HM_DATA/${BDLIB}/archive/@YYYY@/@MM@/@DD@/@HH@   # Boundary file directory,
                                                        # For more information, read in scr/Boundary_strategy.pl
SST_SOURCES=$HOST_MODEL                 # List of external SST sources like $HOST_MODEL|HIROMB|NEMO|ROMS|ECE|RACMO
                                        # See util/gl/ala/merge_ocean.F90 for more details
SST_IS_LSM="auto"                       # Switch for using SST as LSM (lsm|sst|auto)
SSTSIC_UPD="yes"                        # (yes|no) Switch to update SST/SIC during forecast

INT_BDFILE=$WRK/ELSCF${CNMEXP}ALBC@NNN@                 # Interpolated boundary file name and location

BDSTRATEGY=era5                 # Which boundary strategy to follow
                                # as defined in scr/Boundary_strategy.pl
                                #
                                # available            : Search for available files in BDDIR, try to keep forecast consistency
                                #                        This is ment to be used operationally.
                                # available_dis_[ens|det] : Search for available ENS/HRES files in BDDIR expecting dissemination style file content, 
                                #                           try to keep forecast consistency. This is ment to be used operationally. 
                                # simulate_operational[_dis[_ens|_det]] : Mimic the behaviour of the operational runs using ECMWF LBC, ie
                                #                        6h old boundaries at 00,06,12,18
                                #                        7-11h at the other cycles
                                # simulate_metcoop     : Mimic the behaviour of the MetCoOp operational runs using ECMWF LBC ie
                                #                        6h old boundaries at 00,06,12,18
                                #                        3h old boundaries at 03,09,15,21
                                # same_forecast        : Use all boundaries from the same forecast, start from analysis
                                # analysis_only        : Use only analysises as boundaries
                                # era                  : As for analysis_only but using ERA interim data
                                # e40                  : As for analysis_only but using ERA40 data
                                # era5                 : As for analysis_only but using ERA5 data (ERA5.1 for 2000-2006)
                                # latest               : Use the latest possible boundary with the shortest forecast length
                                # RCR_operational      : Mimic the behaviour of the RCR runs, ie
                                #                        12h old boundaries at 00 and 12 and
                                #                        06h old boundaries at 06 and 18

                                # Special ensemble strategies
                                # Only meaningful with ENSMSEL non-empty, i.e., ENSSIZE > 0

                                # enda                 : use ECMWF ENDA data for running ensemble data assimilation
                                #                        or generation of background statistic.
                                #                        Note that only LL up to 9h is supported
                                #                        with this you should set your ENSMSEL members
                                # eps_ec               : ECMWF ENS members from the GLAMEPS ECFS archive.
                                #                        Data available from Feb 2013 - June 2019
                                # eps_ec_oper          : ECMWF ENS members from the operational archives
                                #                        note that data has a limited lifetime in MARS

BDINT=3                         # Boundary interval in hours
PERTDIA_BDINT=6                 # Perturbation diagnostics interval
MARS_STAGE="yes"                # Run MARS STAGE before RETRIEVE (yes|no)
NFPBOYD=1                       # Used in the E927 script for creating boundaries - see nam/harmonie_namelists.pm : 
                                #                         %e927 => NAMFPC => 'NFPBOYD' => &Env_or('NFPBOYD','1'),
                                # Set to 1 to allow extra points outside your domain in order to find Semi-Lagrangian departure points outside
                                # Set to 0 to not allow extra points and just truncate the S-L trajectory at the boundary
if [[ "$ANAATMO" = "4DVAR" ]]; then
  NFPBOYD=0                     # Enforces low resolution first guess/boundaries are contained with/in the high-resolution domain
elif [[ "$HOST_MODEL" != "ifs" ]] ; then
  NFPBOYD=1                     # This allows nested arome->arome domains to work correctly
fi


# *** Ensemble mode general settings. ***
# *** For member specific settings use suites/harmonie.pm ***
ENSMSEL=                                # Ensemble member selection, comma separated list, and/or range(s):
                                        # m1,m2,m3-m4,m5-m6:step    mb-me == mb-me:1 == mb,mb+1,mb+2,...,me
                                        # 0=control. ENSMFIRST, ENSMLAST, ENSSIZE derived automatically from ENSMSEL.
ENSINIPERT=bnd                          # Ensemble perturbation method (bnd|randb)
                                        # bnd     : PertAna
                                        # randb   : Perturbation of B-matrix
	                                # cnstr   : constructed perturbations 
EPERT_MODE="after"                      # add IC perturbations before/after analysis in EPS mode
LDIAGENSEVOL="no"                       # ensemble evolution diagnostics : yes/no
CLOUDANALYSIS="no"                    # analysis of cloud varables : yes/no
TFENSDIAG=8
ENSCTL=                                 # Which member is my control member? Needed for ENSINIPERT=bnd. See harmonie.pm.
ENSCTL_IS_PRESENT=yes                   # Is the control available for other members? 
ENSBDMBR=                               # Which host member is used for my boundaries? Use harmonie.pm to set.

SCALE_PERT=yes                          # Scale perturbations based on energy norm and
EREF=35000.                             # energy reference
SLAFK=1.0                               # best set in harmonie.pm
SLAFLAG=0                               # --- " ---
SLAFDIFF=0                              # --- " ---

ENS_BD_CLUSTER=no                       # Switch on clustering for ENS data. Only has a meaning if BDSTRATEGY=eps_ec_oper
REARCHIVE_EPS_EC_OPER=no                # Rearchive ENS data on ECFS
USE_REARCHIVE_EPS_EC_OPER=no            # Use rearchived ENS data on ECFS
ECFS_EPS_EC_BD_PATH=${ECFSLOC}:/$USER/harmonie/$EXP    # Location for rearchiving

EPS_IFS_SST_SOURCE="auto"    # In case of ensemble run take SST from the general boundaries,
                             # set to HRES to reproduce the previous behaviour
                             # After CY48r1, introduced 2023-06-27, it should be possible to use 
                             # IFSENS but this depends on how your data was extracted to your archive

# **** SPP Stochastically Perturbed Parameterizations ***
SPP=no                                  # Activate LSPP (no|yes)
                                        # Should be 'no' here, but see below for ensemble setup (non-empty ENSMSEL)
SDEV_SPP=1.0                            # Standard deviation
TAU_SPP=43200.                          # Time scale (seconds)
XLCOR_SPP=200000.                       # Length scale (m)
SPGQ_SPP=0.5                            # only used for LSPG_SDT=T
SPGADTMIN_SPP=0.15                      # -"-
SPGADTMAX_SPP=3.0                       # -"-
NPATFR_SPP=-1                           # Frequencey to evolve pattern >0 in timesteps, <0 in hours
SPP_DIAG=no                             # Activate output of SPP diagnostics
export LSPP SDEV_SPP TAU_SPP XLCOR_SPP SPGQ_SPP SPGADTMIN_SPP SPGADTMAX_SPP NPATFR_SPP SPP_DIAG

# Physics diagnostics
TEND_DIAG=no                           # Output of tendencies from physics (no|yes)

# *** This part is for EDA with observations perturbation
# Only active in ensemble mode
PERTATMO=CCMA                           # ECMAIN  : In-line observation perturbation using the default IFS way.
                                        # CCMA    : Perturbation of the active observations only (CCMA content)
                                        #           before the Minimization, using the PERTCMA executable.
                                        # none    : no perturbation of upper-air observations

PERTSURF=model                          # ECMA    : perturb also the surface observation before Canari (recommended
                                        #         : for EDA to have full perturbation of the initial state).
                                        # model   : perturb surface fields in grid-point space (recursive filter)
                                        # none    : no perturbation for surface observations.

FESTAT=no                               # Extract differences and do Jb calculations (no|yes)

# **** Aerosol choices (USEAERO implies aerosol usage in physics via forecast_model_settings) ****
USEAERO=transientaod                        # Aerosol usage: tegenaod | transientaod | camsnrt | camscms | noaero | [mocanrt]
AERO_DATA_PATH=/perm/suaj/MERRA2_ASCII/     # Path to aerosol data (monthly files) when USEAERO=transientaod.
AERO_FILE=aero.MERRA2.@YYYY@@MM@.txt    # File name pattern for monthly aerosol data when USEAERO=transientaod.

# **** Climate files ****
CREATE_CLIMATE=${CREATE_CLIMATE-yes}    # Run climate generation (yes|no)
CLIMDIR=$HM_DATA/climate/$DOMAIN        # Climate files directory
BDCLIM=$HM_DATA/${BDLIB}/climate        # Boundary climate files (ald2ald,ald2aro)
                                        # This should point to intermediate aladin
                                        # climate file in case of hir2aro,ifs2aro processes.
ECOCLIMAP_PARAM_BINDIR=$HM_DATA/climate # Binary cover param files directory

# Physiography input for SURFEX
USE_ONE_DECADE=${USE_ONE_DECADE-no}
ECOCLIMAP_VERSION=SG                    # Version of ECOCLIMAP for surfex
                                        # Available versions are 1.1-1.5,2.0-2.2,2.2.1,2.5_plus and SG
                                        # FLake requires 2.5_plus or SG
ECOSG_VERSION=0.1                       # Versions of ECOCLIMAP-SG (0.1|1.2)
                                        # For version 1.2, set HM_CLDATA=/hpcperm/ic0/pgd/uwc in Env_system
XSCALE_H_TREE=1.0                       # Scale the tree height with this factor
# Activate inclusion of fake trees for open land VEGTYPEs. The vector positions represent:
# 1 NVT_BOGR, 2 NVT_GRAS, 3 NVT_TROG, 4 NVT_C3W, 5 NVT_C3S, 6 NVT_C4, 7 NVT_FLGR
LFAKETREE=.F.,.T.,.T.,.T.,.T.,.T.,.T.
LDB_VERSION=3.0                         # Lake database version SG|3.0
                                        # For SG, set HM_CLDATA=/hpcperm/ic0/pgd/uwc in Env_system
SOIL_TEXTURE_VERSION=SOILGRID           # Soil texture input data FAO|HWSD_v2|SOILGRID|SOILGRID_v2

# Path to pre-generated domains, in use if USE_REF_CLIMDIR=yes set in Env_system
# Saves time for quick experiments
REF_CLIMDIR=ec:/hlam/harmonie_climdir/release-43h2.1.1/$DOMAIN/$GRID_TYPE/$ECOCLIMAP_VERSION

# **** Archiving settings ****
ARCHIVE_ECMWF=yes                       # Archive to $ECFSLOC at ECMWF (yes|no)
# Archiving selection syntax, settings done below
#
# [fc|an|pp]_[fa|gr|nc] : Output from
#  an : All steps from upper air and surface analysis
#  fc : Forecast model state files from upper air and surfex
#  pp : Output from FULLPOS and SURFEX_LSELECT=yes (ICMSHSELE+NNNN.sfx)
# in any of the formats if applicable
#  fa : FA files
#  gr : GRIB[1|2] files
#  nc : NetCDF files
# sqlite|odb|VARBC|bdstrategy : odb and sqlite files stored in odb_stuff.tar
# fldver|ddh|vobs|vfld : fldver/ddh/vobs/vfld files
# climate : Climate files from PGD and E923
# Some macros
# odb_stuff=odb:VARBC:bdstrategy:sqlite
# verif=vobs:vfld
# fg : Required files to run the next cycle


# **** Cycles to run, and their forecast length ****
TFLAG="h"                               # Time flag for model output. (h|min)
                                        # h   = hour based output
                                        # min = minute based output

# The unit of HWRITUPTIMES, FULLFATIMES, ..., SFXFWFTIMES should be:
#   - hours   if TFLAG="h"
#   - minutes if TFLAG="min"

# Writeup times of # history,surfex and fullpos files
# Comma separated list, and/or range(s) like:
# t1,t2,t3-t4,t5-t6:step    tb-te == tb-te:1 == tb,tb+1,tb+2,...,te

if [ "$SIMULATION_TYPE" = "climate" ]; then  

  # Specific settings for climate simulations

  HH_LIST="00"                            # Which cycles to run, replaces FCINT                             | Irrelevant for climate simulations, but needs to be set
  LL_LIST="3"                             # Forecast lengths for the cycles [h], replaces LL, LLMAIN        | Irrelevant for climate simulations, but needs to be set
                                          # The LL_LIST list is wrapped around if necessary, to fit HH_LIST
  HWRITUPTIMES="0"                        # History file output times, last step of cycle automatically appended
  FULLFAFTIMES="$HWRITUPTIMES"            # History FA file IO server gather times. Must be equal to HWRITUPTIMES as convertFA cannot handle IOserver parts
  PWRITUPTIMES="00-760:1"                 # Postprocessing times
  PFFULLWFTIMES=$PWRITUPTIMES             # Postprocessing FA file IO server gathering times
  VERITIMES=$HWRITUPTIMES                 # Verification output times, changes PWRITUPTIMES/SFXELTIMES
  SFXSELTIMES="00-760:1"                  # Surfex select file output times - Only meaningful if SURFEX_LSELECT=yes
  SFXSWFTIMES=$SFXSELTIMES                # SURFEX select FA file IO server gathering times
  SWRITUPTIMES="0"                        # Surfex model state output times, last step of cycle automatically appended
  SFXWFTIMES=$SWRITUPTIMES                # SURFEX history FA file IO server gathering times

  ARSTRATEGY="climate:fg:odb_stuff: \
              an_fa:pp_nc"                # Files to archive on ECFS, see above for syntax

elif [ -z "$ENSMSEL" ] ; then

  # Standard deterministic run

  HH_LIST="00-21:3"                       # Which cycles to run, replaces FCINT
  LL_LIST="12,3"                          # Forecast lengths for the cycles [h], replaces LL, LLMAIN
                                          # The LL_LIST list is wrapped around if necessary, to fit HH_LIST
  HWRITUPTIMES="00-21:3,24-60:6"          # History file output times
  FULLFAFTIMES=$HWRITUPTIMES              # History FA file IO server gather times
  PWRITUPTIMES="00-60:3"                  # Postprocessing times
  PFFULLWFTIMES=$PWRITUPTIMES             # Postprocessing FA file IO server gathering times
  VERITIMES="00-60:1"                     # Verification output times, changes PWRITUPTIMES/SFXSELTIMES
  SFXSELTIMES=$PWRITUPTIMES               # Surfex select file output times
                                          # Only meaningful if SURFEX_LSELECT=yes
  SFXSWFTIMES=$SFXSELTIMES                # SURFEX select FA file IO server gathering times
  SWRITUPTIMES="00-06:3"                  # Surfex model state output times
  SFXWFTIMES=$SWRITUPTIMES                # SURFEX history FA file IO server gathering times

  ARSTRATEGY="climate:fg:verif:odb_stuff: \
              [an|fc]_fa:pp_gr: \
              _nc:_json"                  # Files to archive on ECFS, see above for syntax

else

  # EPS settings
  # Note that member specific settings like e.g. for the control member (0)
  # are found in suites/harmonie.pm

  SPP=yes                                 # Default yes for perturbed members
  HH_LIST="00-21:3"                       # Which cycles to run, replaces FCINT
  LL_LIST="48,3,3,3,3,3,3,3"              # Forecast lengths for the cycles [h], replaces LL, LLMAIN
  HWRITUPTIMES="00-48:3"                  # History file output times
  FULLFAFTIMES=$HWRITUPTIMES              # History FA file IO server gather times
  PWRITUPTIMES="00-48:3"                  # Postprocessing times
  PFFULLWFTIMES=$PWRITUPTIMES             # Postprocessing FA file IO server gathering times
  VERITIMES="00-60:3"                     # Verification output times, changes PWRITUPTIMES/SFXSELTIMES
  SFXSELTIMES=$PWRITUPTIMES               # Surfex select file output times
                                          # Only meaningful if SURFEX_LSELECT=yes
  SFXSWFTIMES=$SFXSELTIMES                # SURFEX select FA file IO server gathering times
  SWRITUPTIMES="00-06:3"                  # Surfex model state output times
  SFXWFTIMES=$SWRITUPTIMES                # SURFEX history FA file IO server gathering times

  ARSTRATEGY="climate:fg:verif:odb_stuff: \
              [an|fc|pp]_fa:pp_gr: \
              _nc:_json"                  # Files to archive on ECFS, see above for syntax

  CONVERTFA=no

fi

SURFEX_LSELECT="yes"                    # Only write selected fields in surfex outpute files. (yes|no)
                                        # Check nam/surfex_selected_output.pm for details.
                                        # Not tested with lfi files.
INT_SINI_FILE=$WRK/SURFXINI.fa          # Surfex initial file name and location

# **** DDH ****
USEDDH="no"                             # Use DDH. (yes|no)

# **** Postprocessing/output ****
IO_SERVER=yes                           # Use IO server (yes|no). Set the number of cores to be used
                                        # in your Env_submit
IO_SERVER_BD=yes                        # Use IO server for reading of boundary data
POSTP="inline"                          # Postprocessing by Fullpos (inline|offline|none).
                                        # See Select_postp.pl for selection of fields.
                                        # inline: this is run inside of the forecast
                                        # offline: this is run in parallel to the forecast in a separate task

FREQ_RESET_TEMP=24                      # Reset frequency of max/min temperature values in hours, controls NRAZTS
FREQ_RESET_GUST=24                      # Reset frequency of max/min gust values in hours, controls NXGSTPERIOD
                                        # Set to -1 to get the same frequency _AND_ reset behaviour as for min/max temperature
                                        # See yomxfu.F90 for further information.
NTIMEFMT=0                              # Time format in FA output file names
                                        #   0: +{HHHH} or +{step} (if TFLAG=min)
                                        #   1: +{HHHH}:{mm}
                                        #  10: +{HHHH}h
                                        #  11: +{HHHH}h{mm}m
NVGRIB=2                                # Level of GRIB packing for atmosphere FA files
                                        #   0: no packing: large files (ca 4x), slower conversion, no rounding errors after de-accumulation (no negative precip)
                                        #   2: v0mod GRIB: default

# **** Check SP tendency evolution ****
CHKEVO="no"                             # (yes|no). If "yes" a CHKEVO_SPTEND file is created in $ARCHIVE
[ $CHKEVO = "yes" ] && POSTP="none"
export LNWECHKEVO=.FALSE.

# PYSURFEX FA
USEEPYGRAM="no"                         # (yes|no). Use epygram to read FA files instead of grib
                                        # for firstguess4gridpp and offline forcing

# **** GRIB/NC ****
SAVE_FAOUTPUT="history:surfex:fullpos: \
               surfexsele"              # Which FA output to save in ARCHIVE after successful conversion by convertFA (colon separated list)
CONVERTFA=${CONVERTFA-yes}              # Conversion of FA file to GRIB/nc (yes|no)
ARCHIVE_FORMAT=nc                       # Format of archive files (GRIB1|GRIB2|nc). nc format yet only available in climate mode
GRIB_BY_FULLPOS=no                      # Let fullpos write GRIB2
NCNAMES=climate                         # Naming of NetCDF files follows (climate|nwp) convention.
NCSEPAR="_"                             # Separarator between components of netcdf file names
RCATDIR=$ARCHIVE_ROOT/RCAT              # Copy nc files in RCATVAR list to freq/var subdirs in this directory (careful: no cleaning applied!)
RCATCPLN=cp                             # Copy or create soft links in the RCATDIR (cp|ln).
RCATVARS=""                             # Copy nc files of these variables to RCATDIR, colon separated list
MAKEGRIB_LISTENERS=1                    # Number of parallel listeners for Makegrib
                                        # Only applicable if ARCHIVE_FORMAT=GRIB[1|2]


# **** Verification extraction ****
OBSEXTR=yes                             # Extract observations from BUFR (yes|no)
FLDEXTR=yes                             # Extract model data for verification from model files (yes|no)
FLDEXTR_TASKS=1                         # Number of parallel tasks for field extraction
VFLDEXP=$EXP                            # Experiment name on vfld files
SCREXTR=no                              # Use Screening (NCONF=002) to produce O-F data
SCREXTR_TASKS=1                         # Number of parallel tasks for O-F extraction
FGREFEXP=${FGREFEXP-undef}              # reference experiment name for FirstGuess
OBREFEXP=${OBREFEXP-undef}              # reference experiment name for ODBs
SCREXTR_FORMAT="sqlite"                 # Output format, either sqlite or parquet

# *** Field verification ***
FLDVER=no                               # Main switch for field verification and analysis increments (yes|no)
FLDVER_HOURS="03"                       # Hours for field verification, for ana-increments the cycling 
                                        # interval must be in the list
AI_ACCUMULATION_CYCLES="ALL" #"00 03 06 09 12 15 18 21"            # Accumlate ana-increments for these cycles
AI_ACCUMULATION_HOURS=720               # Accumulate ana-increments over 30 days (30x24=720)

# *** Observation monitoring ***
OBSMONITOR=obstat                       # Create Observation statistics plots
                                        # Format: OBSMONITOR=Option1:Option2:...:OptionN
                                        # obstat: Daily usage maps and departures
                                        # no: Nothing at all
                                        #
                                        # obstat is # only active if ANAATMO != none
OBSMON_SYNC=no                          # Sync obsmn sqlite tables from HOST1 (if set) to HOST0 (yes|no)

# Recipient(s) to send mails to (you@work,you@home)
MAIL_ON_ABORT=                          # when a task aborts
MAIL_TESTBED=$USER                      # testbed results summary

# Exporting variables for the system
export ARCHIVE_ROOT EXTRARCH BINDIR HH_LIST LL_LIST WRK CLIMDIR REF_CLIMDIR ECOCLIMAP_PARAM_BINDIR MODEL
export BDLIB BDDIR BDINT BDSTRATEGY NBDMAX MARS_EXPVER HOST_MODEL MARS_STAGE
export GRID_TYPE
export TFLAG POSTP CONVERTFA ARCHIVE_FORMAT MAKEGRIB_LISTENERS GRIB_BY_FULLPOS USEEPYGRAM SAVE_FAOUTPUT
export ECFSLOC ECFSGROUP NLBC FCINT DOMAIN BDCLIM LSMIXBC CISBA CSNOW CROUGH SURFEX_SEA_ICE TOPO_SOURCE SURFEX_LAKES
export VERITIMES OBSEXTR FLDEXTR FLDEXTR_TASKS VFLDEXP
export SCREXTR SCREXTR_TASKS FGREFEXP OBREFEXP SCREXTR_FORMAT
export SURFEX_LSELECT CFORCING_FILETYPE
export BUILD CREATE_CLIMATE BUILD_WITH CMAKE_BUILD_TYPE
export COMPILE_DABYFA COMPILE_ENKF
export HWRITUPTIMES SWRITUPTIMES PWRITUPTIMES FLDVER_HOURS FLDVER HOST_SURFEX
export FULLFAFTIMES PFFULLWFTIMES
export SFXSELTIMES SFXWFTIMES SFXSWFTIMES
export ANASURF_MODE EXT_BDDIR EXT_BDFILE EXT_ACCESS JB_INTERPOL JB_REF_DOMAIN SINGLEOBS ANASURF_OI_COEFF
export NPATCH LISBA_CANOPY SURFEX_OFFLINE_BINARIES XRIMAX RADSCHEME
export RSMIN_DECIDUOUS_FACTOR RSMIN_CONIFEROUS_FACTOR RSMIN_C3_FACTOR RSMIN_C4_FACTOR
export XSCALE_H_TREE LFAKETREE
export BDFILE NCNAMES NCSEPAR RCATDIR RCATCPLN RCATVARS
export ANAATMO ANASURF VLEV VER_SDATE ARCHIVE_ECMWF SST_SOURCES SST_IS_LSM SSTSIC_UPD
export OBDIR OBSMONITOR OBSMON_SYNC
export DYNAMICS PHYSICS DFI TAUS TSPAN LGRADSP LSPBDC LUNBC
export CNMEXP RUNNING_MODE MASS_FLUX_SCHEME STATNW HARATU HGT_QS WINDFARM
export INT_BDFILE INT_SINI_FILE WINDFARM_COORDS_FILE
export ECOCLIMAP_VERSION ECOSG_VERSION SOIL_TEXTURE_VERSION LDB_VERSION ECOSG_ALB_VERSION USE_ONE_DECADE
export SIMULATION_TYPE FP_PRECISION
export ARSTRATEGY NTIMEFMT FREQ_RESET_TEMP FREQ_RESET_GUST NVGRIB
export IO_SERVER IO_SERVER_BD
export MAIL_ON_ABORT MAIL_TESTBED
export USE_MSG USE_DFS
export NOUTERLOOP ILRES TSTEP4D NITER4D NSIMU4D TSTEPTRAJ
export TL_TEST AD_TEST CH_RES_SPEC MINPHYSICS
export LBIGEZ_MINIM LBGE_BIGEZ PROLOG_INT_METHOD
export FORCE1 FORCE2
export ADDITIVE_INFLATION HYBRID KHYBRID LETKF_3DSCREEN AI_ARCH LETKF_LAG LETKF_CONTROL
export AUGMENT_CV Q_IN_SP
export CHKEVO
export VERT_DISC ALARO_VERSION NAMELIST_BASE
export PYSURFEX
export LPATCH1
export LOOPS
export PERTATMO PERTSURF SLAFLAG SLAFK SLAFDIFF SPPT SPP TEND_DIAG
export MODIFY_LAKES
export ENSMSEL ENSBDMBR ENSINIPERT ENSCTL FESTAT ENSCTL_IS_PRESENT
export EPERT_MODE
export PERTDIA_BDINT MULTITASK
export ENS_BD_CLUSTER REARCHIVE_EPS_EC_OPER USE_REARCHIVE_EPS_EC_OPER ECFS_EPS_EC_BD_PATH
export SCALE_PERT EREF
export XZ0SN XZ0HSN XCGMAX CV_LOWVEG CV_HIGHVEG XCSMAX XALLEN_TERM XGRASS_H_DNM
export XCD_COEFF1 XCD_COEFF2 XCH_COEFF1
export H_TREE_FILE
export USEAERO AERO_DATA_PATH AERO_FILE
export AI_ACCUMULATION_CYCLES AI_ACCUMULATION_HOURS
export IAUVAR LVARCONS
export EPS_IFS_SST_SOURCE
export USEDDH
export LDIAGENSEVOL TFENSDIAG CLOUDANALYSIS
export NFPBOYD
# Define your testbed list here
# The definition of the different configurations can be found in scr/Harmonie_testbed.pl
export TESTBED_LIST="AROME AROME_1D \
                     AROME_BD_ARO AROME_BD_ARO_IO_SERV \
                     AROME_CLIMSIM ALADIN_CLIMSIM"

PGD_INP="DIRECT"
if [ "$PGD_INP" == "NETCDF" ]; then
  export GMTED2010_OUTPUT_FORMAT="NETCDF"
  export SOILGRID_OUTPUT_FORMAT="NETCDF"
  export TOPO_INPUT_FORMAT="NETCDF"
  export SOC_INPUT_FORMAT="NETCDF"
  export SAND_CLAY_INPUT_FORMAT="NETCDF"
  export ECOCLIMAP_COVER_FORMAT="NETCDF"
  export FLAKE_GDB_INPUT_FORMAT="NETCDF"
  export ECOSG_INPUT_FORMAT="NETCDF"
else
  export GMTED2010_OUTPUT_FORMAT="DIRECT"
  export SOILGRID_OUTPUT_FORMAT="DIRECT"
  export TOPO_INPUT_FORMAT="DIRECT"
  export SOC_INPUT_FORMAT="DIRECT"
  export SAND_CLAY_INPUT_FORMAT="DIRECT"
  export ECOCLIMAP_COVER_FORMAT="DIRECT"
  export FLAKE_GDB_INPUT_FORMAT="DIRECT"
  export ECOSG_INPUT_FORMAT="DIRTYP"
fi
