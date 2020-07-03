/* 
 * File:   timer.h
 * Author: Scott
 *
 * Created on April 6, 2018, 9:14 PM
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" 
#endif


bool timer_has_time_elapsed(uint32_t time, uint32_t num_ms);
uint32_t timer_get_ticks();


#ifdef	__cplusplus

#endif

#endif	/* TIMER_H */

