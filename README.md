# LightweightMPIprofiling
Lightweigh MPI profiling

HOW TO USE
1. simply modify the Makefile, and make. You'll see a libmpit.a in the same directory.
2. instrument the application code.
    PROFILE_X_INIT() and PROFILE_X_FINISH() indict start and pause the profiling for code region X.
    X here has 6 options, it is sepecially designed for CESM.
    DYNAMIC, PHYSICS, BAROTROPIC, BAROCLINIC, LND, ICE
3. compile the code linking with -L/<toolpath>/ -lmpit


OUTPUT:
each mpi rank will generate a file named mpi_record.$rankid.
In the file, it contains the mpi operations and its corresponding time, message count and message volume in each code region.
