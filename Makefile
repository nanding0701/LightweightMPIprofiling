CC =cc
OPT=-O3 
#CFLAGS = -DDEBUG -I/cm/shared/apps/intel-cluster-tools/impi/3.2.0.011/include64
#CFLAGS = -I/home/software/intel/impi/4.0.0.025/intel64/include
#CFLAGS = -I/home/software/intel/15.0/impi/5.0.3.048/intel64/include
DEF= -DPERF_PROFILE -DATM -DLND -DICE -DOCN 
AR = ar
ARTAG = rcv

libmpit	: profile.o timer.o mpiwrapper.o mpiwrapper_f.o
	$(AR) $(ARTAG) libmpit.a mpiwrapper.o mpiwrapper_f.o timer.o profile.o
	$(RM) -f *.o
profile.o : profile.c	
	$(CC) $(CFLAGS) $(DEF) -c profile.c
mpiwrapper.o: mpiwrapper.c
	$(CC) $(CFLAGS) $(DEF) -c mpiwrapper.c
mpiwrapper_f.o: mpiwrapper_f.c
	$(CC) $(CFLAGS) $(DEF) -c mpiwrapper_f.c 
timer.o : timer.c	
	$(CC) $(CFLAGS) -c timer.c
clean :
	rm -f *.o	rm -f libmpit.a
