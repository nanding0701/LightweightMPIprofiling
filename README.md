# LightweightMPIprofiling
Build library
  1. modify the Makefile, and then make, you'll see libmpit.a in the current directory.

Instrument application code
  1. support six regions cocurrently. APIs are:
      PROFILE_DYNAMIC_INIT() and PROFILE_DYNAMIC_FINISH()
      PROFILE_PHYSICS_INIT() and PROFILE_PHYSICS_FINISH()
      PROFILE_BAROCLINIC_INIT() and PROFILE_BAROCLINIC_FINISH()
      PROFILE_BAROTROPIC_INIT() and PROFILE_BAROTROPIC_FINISH()
      PROFILE_ICE_INIT() and PROFILE_ICE_FINISH()
      PROFILE_LND_INIT() and PROFILE_LNDFINISH()
      
  2. Example (fortran code) 
    call PROFILE_DYNAMIC_INIT()
    ...
    call PROFILE_DYNAMIC_FINISH()
  
 Build application code
  need to link libmpit.a
  
  
 Outputs:
  each mpi rank will generate one file. In this file, all the mpi opreations is listed for each regions (six in total).
 

