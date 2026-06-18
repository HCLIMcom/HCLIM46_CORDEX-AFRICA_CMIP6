# AFRICA-CORDEX simulations
# --------------------------------------------------
Experiment folders for the AFRICA-CORDEX simulations.

HCLIM version:
- cycle 46
- commit 05737c7353aac29b45cdc02ce0ebad8bad1bb9d2

Current experiments:
- ERA-5 evaluation run

-------

Before running:
- Double check ECMWF account, output paths in Env_submit and Env_system.
- Double check settings in ecf/config_exp.h
- Double check surfex output and surfex namelist in nam.

--------
### Planned simulations
 
| Experiment name                              | Institution | HPC          | Domain | LBC data               | Simulation period | DTGBEG     | DTGEND     |
| :------------------------------------------- | :---------- | :----------- | :----- | :--------------------- | :---------------- | :----------| :--------  |
| AFR22_ALADIN43_v1_ERA5_r1i1p1f1_eval         | DMI         | ATOS (ECMWF) | AFR-22 | ERA-5                  | Evaluation        | 1979080100 | ?          |

--------

Test experiment (1 month | ERA-5 driven):
/ec/res4/scratch/suaj/hm_home/AFR22_ALADIN43_v1_ERA5_r1i1p1f1_eval
