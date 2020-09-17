#ifndef TIMER_H
#define TIMER_H

double	current_time(void);

void	_timer_clear(int n);
void	_timer_start(int n);
void	_timer_stop(int n);
double	_timer_read(int n);

void    _physics_timer_clear(int n);
void    _timer_physics_start(int n);
void    _timer_physics_stop(int n);
double  _timer_physics_read(int n);

void    _dynamic_timer_clear(int n);
void    _timer_dynamic_start(int n);
void    _timer_dynamic_stop(int n);
double  _timer_dynamic_read(int n);

void    _baroclinic_timer_clear(int n);
void    _timer_baroclinic_start(int n);
void    _timer_baroclinic_stop(int n);
double  _timer_baroclinic_read(int n);

void    _barotropic_timer_clear(int n);
void    _timer_barotropic_start(int n);
void    _timer_barotropic_stop(int n);
double  _timer_barotropic_read(int n);

void    _lnd_timer_clear(int n);
void    _timer_lnd_start(int n);
void    _timer_lnd_stop(int n);
double  _timer_lnd_read(int n);

void    _ice_timer_clear(int n);
void    _timer_ice_start(int n);
void    _timer_ice_stop(int n);
double  _timer_ice_read(int n);

#endif

