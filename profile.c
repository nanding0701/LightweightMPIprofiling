#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mpi.h"
#include "profile.h"
#include "timer.h"
#include "day.h"
#include "mpiname.h"
#include "component.h"

int    proc_id = 0; 
int    profile_on = 1;
int    threshold;
int    date = 0;
double comm_time;

static mpi_perf mpi_physics_profile[MPI_FUNCTIONS];
double used_physics_time = 0.0, comm_physics_time = 0.0, comp_physics_time = 0.0,elapsed_physics_time = 0.0;

static mpi_perf mpi_dynamic_profile[MPI_FUNCTIONS];
double used_dynamic_time = 0.0, comm_dynamic_time = 0.0, comp_dynamic_time = 0.0,elapsed_dynamic_time = 0.0;

static mpi_perf mpi_baroclinic_profile[MPI_FUNCTIONS];
double used_baroclinic_time = 0.0, comm_baroclinic_time = 0.0;
double comp_baroclinic_time = 0.0,elapsed_baroclinic_time = 0.0;


static mpi_perf mpi_barotropic_profile[MPI_FUNCTIONS];
double used_barotropic_time = 0.0, comm_barotropic_time = 0.0;
double comp_barotropic_time = 0.0, elapsed_barotropic_time = 0.0;

static mpi_perf mpi_lnd_profile[MPI_FUNCTIONS];
double used_lnd_time = 0.0, comm_lnd_time = 0.0, comp_lnd_time = 0.0,elapsed_lnd_time = 0.0;

static mpi_perf mpi_ice_profile[MPI_FUNCTIONS];
double used_ice_time = 0.0, comm_ice_time = 0.0, comp_ice_time = 0.0,elapsed_ice_time = 0.0;

FILE*  profile_file;
static mpi_store mpi_record[KERNEL][MPI_FUNCTIONS];


void sort_mpi(int model, mpi_store *_mpi_sort[KERNEL][MPI_FUNCTIONS]);

void PROFILE_INIT(int process_id){

     char profile_name[100];
     int m,i,j,k;

     for(m=0;m<KERNEL;m++){
	for (i=0; i<MPI_FUNCTIONS; i++){
           mpi_record[m][i].total_time = 0.0;
           mpi_record[m][i].comm_time = 0.0;
           mpi_record[m][i].comp_time = 0.0;
           mpi_record[m][i].comm_size = 0; 
           mpi_record[m][i].count = 0;
           mpi_record[m][i].flag = 0;
        }
    }
     
     proc_id = process_id;
       	
     sprintf(profile_name, "mpi_record.%d", proc_id);
     profile_file = fopen(profile_name, "w");
     if (profile_file == NULL){
          printf("Open profile file failed\n");
          exit(0);
     } 

     #ifdef MPI_TIME
       mpi_profile[25].flag = 1;
       mpi_profile[26].flag = 1;
       threshold = 2000;
     #endif

}

void PROFILE_PHYSICS_INIT(){

        _timer_physics_start(0);
        int i;

        for (i=0; i<MPI_FUNCTIONS; i++){
            mpi_physics_profile[i].entry_time = 0.0;
            mpi_physics_profile[i].total_time = 0.0;
            mpi_physics_profile[i].count = 0;
            mpi_physics_profile[i].flag = 0;
        }

}



void profile_physics_init_(){
    PROFILE_PHYSICS_INIT();
}


void PROFILE_DYNAMIC_INIT(){

        _timer_dynamic_start(0);

      int i;

        for (i=0; i<MPI_FUNCTIONS; i++){
                mpi_dynamic_profile[i].entry_time = 0.0;
                mpi_dynamic_profile[i].total_time = 0.0;
                mpi_dynamic_profile[i].count = 0;
                mpi_dynamic_profile[i].flag = 0;
                  
        }

}

void profile_dynamic_init_(){
    PROFILE_DYNAMIC_INIT();
}

void PROFILE_BAROCLINIC_INIT(){

        _timer_baroclinic_start(0);

       int i;

        for (i=0; i<MPI_FUNCTIONS; i++){
                mpi_baroclinic_profile[i].entry_time = 0.0;
                mpi_baroclinic_profile[i].total_time = 0.0;
                mpi_baroclinic_profile[i].count = 0;
                mpi_baroclinic_profile[i].flag = 0;
//                mpi_ocn_profile[i].middle_time = 0.0;
                  
        }
     //   proc_ocn_id = proc_id;
     //   date = ymd;
     //   hour = model_hour;
   
}

void profile_baroclinic_init_(){
    PROFILE_BAROCLINIC_INIT();
}

void PROFILE_BAROTROPIC_INIT(){

        _timer_barotropic_start(0);

        int i;

        for (i=0; i<MPI_FUNCTIONS; i++){
                mpi_barotropic_profile[i].entry_time = 0.0;
                mpi_barotropic_profile[i].total_time = 0.0;
                mpi_barotropic_profile[i].count = 0;
                mpi_barotropic_profile[i].flag = 0;
//                mpi_ocn_profile[i].middle_time = 0.0;
                  
        }
     //   proc_ocn_id = proc_id;
     //   date = ymd;
     //   hour = model_hour;
     
}

void profile_barotropic_init_(){
    PROFILE_BAROTROPIC_INIT();
}


void PROFILE_ICE_INIT(){

        _timer_ice_start(0);

        int i;
 //       int id;
//        id=proc_id;
//printf("You are now in the profile_ice_init with rank=%d\n",id);
        for (i=0; i<MPI_FUNCTIONS; i++){
                mpi_ice_profile[i].entry_time = 0.0;
                mpi_ice_profile[i].total_time = 0.0;
                mpi_ice_profile[i].count = 0;
                mpi_ice_profile[i].flag = 0;
//                mpi_ice_profile[i].middle_time = 0.0;
        }
    //    proc_ice_id = proc_id;
    //    date = ymd;
   //     hour = model_hour;
 
}

void profile_ice_init_(){
  PROFILE_ICE_INIT();
}

void PROFILE_LND_INIT(){


        _timer_lnd_start(0);

        int i;

        for (i=0; i<MPI_FUNCTIONS; i++){
                mpi_lnd_profile[i].entry_time = 0.0;
                mpi_lnd_profile[i].total_time = 0.0;
                mpi_lnd_profile[i].count = 0;
                mpi_lnd_profile[i].flag = 0;
 //               mpi_lnd_profile[i].middle_time = 0.0;
        }
      //  proc_lnd_id = proc_id;
      //  date = ymd;
      //  hour = model_hour;

}

void profile_lnd_init_(){
   PROFILE_LND_INIT();
}


void PROFILE_ON(){

	// Default is ON. 
	profile_on = 1;
}

void PROFILE_OFF(){

	profile_on = 0;
}

void PROFILE_START(int mpi_id){

	if (profile_on){
		mpi_physics_profile[mpi_id].entry_time = current_time();
                mpi_dynamic_profile[mpi_id].entry_time = current_time();
                mpi_baroclinic_profile[mpi_id].entry_time = current_time();
                mpi_barotropic_profile[mpi_id].entry_time = current_time();
                mpi_lnd_profile[mpi_id].entry_time = current_time();
                mpi_ice_profile[mpi_id].entry_time = current_time();
           
       }
}


void PROFILE_STOP(int mpi_id,int size){	
	
	if (profile_on){
		used_physics_time = current_time() - mpi_physics_profile[mpi_id].entry_time;
		mpi_physics_profile[mpi_id].total_time += used_physics_time;
		(mpi_physics_profile[mpi_id].count)++;
                mpi_physics_profile[mpi_id].comm_size += size;
	

                used_baroclinic_time = current_time() - mpi_baroclinic_profile[mpi_id].entry_time;
                mpi_baroclinic_profile[mpi_id].total_time += used_baroclinic_time;
                (mpi_baroclinic_profile[mpi_id].count)++;
		mpi_baroclinic_profile[mpi_id].comm_size += size;
           
                used_barotropic_time = current_time() - mpi_barotropic_profile[mpi_id].entry_time;
                mpi_barotropic_profile[mpi_id].total_time += used_barotropic_time;
                (mpi_barotropic_profile[mpi_id].count)++;
                mpi_barotropic_profile[mpi_id].comm_size += size;
        
                used_dynamic_time = current_time() - mpi_dynamic_profile[mpi_id].entry_time;
		mpi_dynamic_profile[mpi_id].total_time += used_dynamic_time;
		(mpi_dynamic_profile[mpi_id].count)++;
                mpi_dynamic_profile[mpi_id].comm_size +=size;

                used_lnd_time = current_time() - mpi_lnd_profile[mpi_id].entry_time;
                mpi_lnd_profile[mpi_id].total_time += used_lnd_time;
                (mpi_lnd_profile[mpi_id].count)++;
                mpi_lnd_profile[mpi_id].comm_size+=size;

                used_ice_time = current_time() - mpi_ice_profile[mpi_id].entry_time;
                mpi_ice_profile[mpi_id].total_time += used_ice_time;
                (mpi_ice_profile[mpi_id].count)++;
                mpi_ice_profile[mpi_id].comm_size += size;
	}

}

void PROFILE_PHYSICS_FINISH(){

        int i,j;
        _timer_physics_stop(0);
       elapsed_physics_time = _timer_physics_read(0);    

        for(i=0; i<MPI_FUNCTIONS; i++)
        {
                mpi_record[0][i].comm_time += mpi_physics_profile[i].total_time;
                mpi_record[0][i].count += mpi_physics_profile[i].count;
		mpi_record[0][i].comm_size += mpi_physics_profile[i].comm_size;
       }
        mpi_record[0][0].total_time += elapsed_physics_time;
        _physics_timer_clear(0);
}

void profile_physics_finish_(){
   PROFILE_PHYSICS_FINISH();
 }


void PROFILE_DYNAMIC_FINISH(){

        int i,j;
        _timer_dynamic_stop(0);
        elapsed_dynamic_time = _timer_dynamic_read(0);

        for(i=0; i<MPI_FUNCTIONS; i++){   
            mpi_record[1][i].comm_time += mpi_dynamic_profile[i].total_time;
            mpi_record[1][i].count += mpi_dynamic_profile[i].count;
            mpi_record[1][i].comm_size += mpi_dynamic_profile[i].comm_size;
         }   
        mpi_record[1][0].total_time += elapsed_dynamic_time;
 //       mpi_record[1][date][hour][0].comp_time = elapsed_ocn_time - comm_ocn_time;
        _dynamic_timer_clear(0);
}

void profile_dynamic_finish_(){
   PROFILE_DYNAMIC_FINISH();
 }

void PROFILE_BAROCLINIC_FINISH(){

        int i,j;
        _timer_baroclinic_stop(0);
       elapsed_baroclinic_time = _timer_baroclinic_read(0);

          for(i=0; i<MPI_FUNCTIONS; i++){   
            mpi_record[2][i].comm_time += mpi_baroclinic_profile[i].total_time;
            mpi_record[2][i].count += mpi_baroclinic_profile[i].count;
            mpi_record[2][i].comm_size +=mpi_baroclinic_profile[i].comm_size;
      //       comm_baroclinic_time += mpi_baroclinic_profile[i].total_time;
          }   
        mpi_record[2][0].total_time += elapsed_baroclinic_time;
   //     mpi_record[2][date][hour][0].comp_time = elapsed_baroclinic_time - comm_baroclinic_time;
        _baroclinic_timer_clear(0);

}

void profile_baroclinic_finish_(){
   PROFILE_BAROCLINIC_FINISH();
 }


void PROFILE_BAROTROPIC_FINISH(){

        int i,j;
        _timer_barotropic_stop(0);
        elapsed_barotropic_time = _timer_barotropic_read(0);

 //       date = ymd;
         for(i=0; i<MPI_FUNCTIONS; i++){   
            mpi_record[3][i].comm_time += mpi_barotropic_profile[i].total_time;
            mpi_record[3][i].count += mpi_barotropic_profile[i].count;
            mpi_record[3][i].comm_size += mpi_barotropic_profile[i].comm_size;
 //           comm_barotropic_time += mpi_barotropic_profile[i].total_time;
          }   
        mpi_record[3][0].total_time += elapsed_barotropic_time;
//        mpi_record[3][date][hour][0].comp_time = elapsed_barotropic_time - comm_barotropic_time;
        _barotropic_timer_clear(0);

}

void profile_barotropic_finish_(){
   PROFILE_BAROTROPIC_FINISH();
 }


void PROFILE_LND_FINISH(){

        int i,j;
        _timer_lnd_stop(0);
        elapsed_lnd_time = _timer_lnd_read(0);


        for(i=0; i<MPI_FUNCTIONS; i++){   
            mpi_record[4][i].comm_time += mpi_lnd_profile[i].total_time;
            mpi_record[4][i].count += mpi_lnd_profile[i].count;
            mpi_record[4][i].comm_size += mpi_lnd_profile[i].comm_size;
   //         comm_lnd_time += mpi_lnd_profile[i].total_time;
          }   
        mpi_record[4][0].total_time += elapsed_lnd_time;
   //     mpi_record[2][date][hour][0].comp_time = elapsed_lnd_time - comm_lnd_time;
        _lnd_timer_clear(0);

}

void profile_lnd_finish_(){
   PROFILE_LND_FINISH();
 }

void PROFILE_ICE_FINISH(){

        int i,j;
	int count_tmp;
        _timer_ice_stop(0);
        elapsed_ice_time = _timer_ice_read(0);

        for(i=0; i<MPI_FUNCTIONS; i++){   

            mpi_record[5][i].comm_time  += mpi_ice_profile[i].total_time;
            mpi_record[5][i].count += mpi_ice_profile[i].count;
            mpi_record[5][i].comm_size += mpi_ice_profile[i].comm_size;
    //        comm_ice_time += mpi_ice_profile[i].total_time;
          }   
        mpi_record[5][0].total_time += elapsed_ice_time;
   //     mpi_record[3][date][hour][0].comp_time = elapsed_ice_time - comm_ice_time;
        _ice_timer_clear(0);
}

void profile_ice_finish_(){
     PROFILE_ICE_FINISH();
}

void PROFILE_FINISH(){

     int m,n,k,i,j;
     int id;
     mpi_store  *mpi_sort[KERNEL][MPI_FUNCTIONS];
      

     id = proc_id;
//printf("1----You are now in the profile_finish with rank=%d\n",id);    

     fprintf(profile_file, "Record communication time each model day\n");
//printf("2----You are now in the profile_finish with rank=%d\n",id);
        for (m=0; m<KERNEL; m++){
            fprintf(profile_file, "Model:%s\n",Kernel[m]);
            fprintf(profile_file, "Func_Name\t\tTime:%d\t\tCount:%d\t\tSize:\n", proc_id, proc_id);

//printf("3---Model:%s\n",Kernel[m]);
//printf("4---Func_Name\t\tTime:%d\t\tCount:%d\t\tSize:\n", proc_id, proc_id);
                     for (k=0; k<MPI_FUNCTIONS; k++){
//printf("5---\n");
                         mpi_sort[m][k] = &mpi_record[m][k];
//printf("6---\n");
                     }
                     sort_mpi(m,mpi_sort);
                     comm_time = 0.0;
                     for(k=0; k<MPI_FUNCTIONS; k++){
                         if (mpi_sort[m][k]->count != 0){
                            n = mpi_sort[m][k] - &mpi_record[m][0];
                            fprintf(profile_file, "%s\t\t%.2f\t\t%ld\t\t%lld\n",MPI_Functions[n], mpi_sort[m][k]->comm_time, mpi_sort[m][k]->count,mpi_sort[m][k]->comm_size);
                            comm_time += mpi_sort[m][k]->comm_time;
                         }
                     }
                     fprintf(profile_file, "total time: %.2f, comm time: %.2f, comp time: %.2f\n", mpi_record[m][0].total_time,comm_time,mpi_record[m][0].total_time-comm_time);

                     fprintf(profile_file, "===============================================================\n");
        }
        fclose(profile_file);
        _timer_clear(0);

}



void sort_mpi(int model,mpi_store *_mpi_sort[KERNEL][MPI_FUNCTIONS]){

	int i, j;
	mpi_store* temp;
        int m,d,h;
        int id;
        m=model;
      
        id=proc_id;
// printf("21---\n");
	for(i=0; i<MPI_FUNCTIONS; i++){
		for(j=i; j<MPI_FUNCTIONS; j++){
// printf("22---\n");
			if (_mpi_sort[m][j]->comm_time > _mpi_sort[m][i]->comm_time){
				temp = _mpi_sort[m][j];
				_mpi_sort[m][j] = _mpi_sort[m][i];
				_mpi_sort[m][i] = temp;
			}
// printf("23---\n");
		}
	}
}

