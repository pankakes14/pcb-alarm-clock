/* 
 * File:   sevenseg.h
 * Author: Scott
 *
 * Created on April 6, 2018, 8:44 PM
 */

#ifndef SEVENSEG_H
#define	SEVENSEG_H

#ifdef	__cplusplus
extern "C" 
#endif


#define SEVENSEG_DIG_UPDATE_PERIOD 2 //amount of time should spend on each digit in ms


//these bit maps actually define which segments are lit up. bit 0 is segment A, 1 is segment B, etc...
#define SEG_0 0x3F
#define SEG_1 0x06
#define SEG_2 0x5B
#define SEG_3 0x4F
#define SEG_4 0x66
#define SEG_5 0x6D
#define SEG_6 0x7D
#define SEG_7 0x07
#define SEG_8 0x7F
#define SEG_9 0x67
#define SEG_A 0x77
#define SEG_B 0x7C
#define SEG_C 0x58
#define SEG_D 0x5E
#define SEG_E 0x79
#define SEG_F 0x71


uint8_t num_to_segstate[16] = {SEG_0, SEG_1, SEG_2, SEG_3, SEG_4, SEG_5, SEG_6, SEG_7, SEG_8, SEG_9, SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F}; 

//current state of the seven segment display
typedef struct _sevenseg_state_t 
{
    uint32_t time_last_update;
    uint32_t time_tick; //temp
    uint8_t current_dig_num;
    uint8_t current_dig_state;
    
    uint8_t digit_states[4]; //this holds the state of the IO port B for each 
    uint8_t digit_nums[4];  //this holds the numbers in each digit
    
    uint8_t PM_STATE;
    
} sevenseg_state_t;

sevenseg_state_t segstate;


void sevenseg_update_display(); //main task 
void init_sevenseg();
void sevenseg_update_digit_state();
void sevenseg_update_counter();
void sevenseg_update_time();
uint8_t sevenseg_translate_num_to_state(uint8_t num);

#ifdef	__cplusplus

#endif

#endif	/* SEVENSEG_H */

