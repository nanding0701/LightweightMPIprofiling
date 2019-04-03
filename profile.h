#ifndef PROFILE_H
#define PROFILE_H

#define MPI_FUNCTIONS 127 
#define PROFILE_DAYS 3
#define PROFILE_HOUR 24
#define KERNEL 6



void PROFILE_INIT(int);
void PROFILE_START(int);
void PROFILE_STOP(int,int);
void PROFILE_FINISH();


void PROFILE_PHYSICS_FINISH();
void PROFILE_PHYSICS_INIT();

void PROFILE_DYNAMIC_FINISH();
void PROFILE_DYNAMIC_INIT();

void PROFILE_BAROCLINIC_FINISH();
void PROFILE_BAROCLINIC_INIT();

void PROFILE_BAROTROPIC_FINISH();
void PROFILE_BAROTROPIC_INIT();

void PROFILE_LND_FINISH();
void PROFILE_LND_INIT();

void PROFILE_ICE_FINISH();
void PROFILE_ICE_INIT();

typedef struct{
	double entry_time;
	double total_time;
	long int count;
	int flag; // Flag for printing elapsed time. Default = 0
        int stop;
        long int comm_size;
}mpi_perf;

typedef struct{
        double total_time;
	double comm_time;
        double comp_time;
        long int count;
        int flag;
//        long int comm_size;
	long long comm_size;
}mpi_store;



#endif /*PROFILE_H*/

