/************************************************************

This file implements linux timer function with gettimeofday.

*************************************************************/
#include "timer.h"
#include <sys/time.h>
#include <stdlib.h>

double current_time(void)
{
	double timestamp;
	struct timeval tv;
	gettimeofday(&tv, 0);
	
	timestamp = (double)((double)(tv.tv_sec*1e6) +(double)tv.tv_usec);
	return timestamp;
}

/**************************************************************
						void WTIME(double);
**************************************************************/

void _wtime(double *t)
{
  static int sec = -1;

  struct timeval tv;
  gettimeofday(&tv, 0);
  if (sec < 0)
        sec = tv.tv_sec;
  *t = (tv.tv_sec - sec)*1.0e6 + tv.tv_usec;
}

/*****************************************************************/
/******         E  L  A  P  S  E  D  _  T  I  M  E          ******/
/*****************************************************************/
double _elapsed_time( void )
{
    double t;

    _wtime( &t );
    return( t );
}

double _elapsed_physics_time( void )
{
    double t;
    _wtime( &t );
    return( t );
}
double _elapsed_dynamic_time( void )
{
    double t;
    _wtime( &t );
    return( t );
}

double _elapsed_barotropic_time( void )
{
    double t;
    _wtime( &t );
    return( t );
}

double _elapsed_baroclinic_time( void )
{
    double t;
    _wtime( &t );
    return( t );
}
double _elapsed_lnd_time( void )
{
    double t;
    _wtime( &t );
    return( t );
}

double _elapsed_ice_time( void )
{
    double t;
    _wtime( &t );
    return( t );
}




double start[64], elapsed[64];
double physics_elapsed[64],lnd_elapsed[64],dynamic_elapsed[64],barotropic_elapsed[64],baroclinic_elapsed[64],ice_elapsed[64];
double physics_start[64],dynamic_start[64],lnd_start[64],ice_start[64],barotropic_start[64],baroclinic_start[64];

/*****************************************************************/
/******            T  I  M  E  R  _  C  L  E  A  R          ******/
/*****************************************************************/
void _timer_clear( int n )
{
    elapsed[n] = 0.0;
}

void _physics_timer_clear( int n )
{
    physics_elapsed[n] = 0.0;
}

void _dynamic_timer_clear( int n )
{ 
    dynamic_elapsed[n] = 0.0;
}

void _barotropic_timer_clear( int n )

{
    barotropic_elapsed[n] = 0.0;
}


void _baroclinic_timer_clear( int n )

{
    baroclinic_elapsed[n] = 0.0;
}

void _lnd_timer_clear( int n )
{
    lnd_elapsed[n] = 0.0;
}

void _ice_timer_clear( int n )
{
    ice_elapsed[n] = 0.0;
}
/*****************************************************************/
/******            T  I  M  E  R  _  S  T  A  R  T          ******/
/*****************************************************************/
void _timer_start( int n )
{
    start[n] = _elapsed_time();
}

void _timer_dynamic_start( int n )
{
    dynamic_start[n] = _elapsed_dynamic_time();
}

void _timer_physics_start( int n )
{
    physics_start[n] = _elapsed_physics_time();
}

void _timer_barotropic_start( int n )
{
    barotropic_start[n] = _elapsed_barotropic_time();
}


void _timer_baroclinic_start( int n )
{
    baroclinic_start[n] = _elapsed_baroclinic_time();
}
void _timer_lnd_start( int n )
{
    lnd_start[n] = _elapsed_lnd_time();
}


void _timer_ice_start( int n )
{
    ice_start[n] = _elapsed_ice_time();
}
/*****************************************************************/
/******            T  I  M  E  R  _  S  T  O  P             ******/
/*****************************************************************/
void _timer_stop( int n )
{
    double t, now;
    now = _elapsed_time();
    t = now - start[n];
    elapsed[n] = t;
}

void _timer_physics_stop( int n )
{
    double t, now;

    now = _elapsed_physics_time();
    t = now - physics_start[n];
    physics_elapsed[n] = t;
}


void _timer_dynamic_stop( int n )
{
    double t, now;

    now = _elapsed_dynamic_time();
    t = now - dynamic_start[n];
    dynamic_elapsed[n] = t;
}


void _timer_barotropic_stop( int n )
{
    double t, now;

    now = _elapsed_barotropic_time();
    t = now - barotropic_start[n];
    barotropic_elapsed[n] = t;
}


void _timer_baroclinic_stop( int n )
{
    double t, now;

    now = _elapsed_baroclinic_time();
    t = now - baroclinic_start[n];
    baroclinic_elapsed[n] = t;
}

void _timer_lnd_stop( int n )
{
    double t, now;

    now = _elapsed_lnd_time();
    t = now - lnd_start[n];
    lnd_elapsed[n] = t;
}

void _timer_ice_stop( int n )
{
    double t, now;

    now = _elapsed_ice_time();
    t = now - ice_start[n];
    ice_elapsed[n] = t;
}
/*****************************************************************/
/******            T  I  M  E  R  _  R  E  A  D             ******/
/*****************************************************************/
double _timer_read( int n )
{
    return( elapsed[n] );
}

double _timer_dynamic_read( int n )
{
    return( dynamic_elapsed[n] );
}

double _timer_physics_read( int n )
{ 
   return( physics_elapsed[n] );
}
double _timer_baroclinic_read( int n )
{
    return( baroclinic_elapsed[n] );
}

double _timer_barotropic_read( int n )
{
    return( barotropic_elapsed[n] );
}

double _timer_lnd_read( int n )
{
    return( lnd_elapsed[n] );
}

double _timer_ice_read( int n )
{
    return( ice_elapsed[n] );
}
