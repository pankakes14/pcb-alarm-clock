/* 
 * File:   util.h
 * Author: stack
 *
 * Created on April 11, 2018, 9:36 PM
 */

#ifndef UTIL_H
#define	UTIL_H

#ifdef	__cplusplus
extern "C" 
#endif

uint8_t generate_random_byte(uint8_t lfsr);
uint8_t get_rand_num(uint8_t lower_bound, uint8_t upper_bound, uint8_t seed);


#ifdef	__cplusplus

#endif

#endif	/* UTIL_H */

