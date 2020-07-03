/* 
 * File:   main.h
 * Author: Scott
 *
 * Created on April 4, 2018, 9:00 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
    
    
#define SYSCLK 48000000 //system clock is 48MHz
    
uint32_t SYSTEM_TICKS = 0;

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

