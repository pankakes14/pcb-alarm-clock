/* 
 * File:   sevenseg.c
 * Author: Scott
 *
 * Created on April 4, 2018, 8:03 PM
 */

#include "main.h"
#include "config.h"
#include "sevenseg.h"
#include "timer.h"
#include "clock.h"
#include "buttons.h"




/* MAIN TASK to update seven segment display. 
 * 
 */
void sevenseg_update_display()
{
    //is it time to move to the next digit
    if (timer_has_time_elapsed(segstate.time_last_update, SEVENSEG_DIG_UPDATE_PERIOD))
    {
        segstate.time_last_update = timer_get_ticks();
        sevenseg_update_digit_state();
        sevenseg_update_time();
    }
    
}


void init_sevenseg()
{
    segstate.current_dig_num = 0;
    segstate.current_dig_state = 0;
    segstate.time_last_update = timer_get_ticks();
    segstate.time_tick = timer_get_ticks();
    
    segstate.digit_states[0] = 0;
    segstate.digit_states[1] = 0;
    segstate.digit_states[2] = 0;
    segstate.digit_states[3] = 0;
    
    segstate.digit_nums[0] = 0;
    segstate.digit_nums[1] = 0;
    segstate.digit_nums[2] = 0;
    segstate.digit_nums[3] = 0;
    
    
}

//this function updates the seven segment display with a free running counter 
//used for debug
void sevenseg_update_counter()
{
        
    if (timer_has_time_elapsed(segstate.time_tick, 25))
    {
        segstate.time_tick = timer_get_ticks();
        
        
        //first update states to numbers from the RTC module
        segstate.digit_nums[3] += 1;
        if (segstate.digit_nums[3] == 10)
        {
            segstate.digit_nums[3] = 0;
            segstate.digit_nums[2] += 1;
        }
        if (segstate.digit_nums[2] == 10)
        {
            segstate.digit_nums[2] = 0;
            segstate.digit_nums[1] += 1;
        }
        if (segstate.digit_nums[1] == 10)
        {
            segstate.digit_nums[1] = 0;
            segstate.digit_nums[0] += 1;
        }
        if (segstate.digit_nums[0] == 10)
        {
            segstate.digit_nums[0] = 0;
        }
        
        segstate.digit_states[0] = sevenseg_translate_num_to_state(segstate.digit_nums[0]);        
        segstate.digit_states[1] = sevenseg_translate_num_to_state(segstate.digit_nums[1]);
        segstate.digit_states[2] = sevenseg_translate_num_to_state(segstate.digit_nums[2]);
        segstate.digit_states[3] = sevenseg_translate_num_to_state(segstate.digit_nums[3]);
        
    }
}

//update the actual time
void sevenseg_update_time()
{
    
    if (timer_has_time_elapsed(segstate.time_tick, 25))
    {
        segstate.time_tick = timer_get_ticks();
        
        
        //first update states to numbers from the RTC module check whether we should 
        //be displaying the alarm time or the normal time
        if (buttstatus.set_alarm_time_pressed)
        {
            segstate.digit_nums[0] = clock_get_alarm_hour_digit(1);    
            segstate.digit_nums[1] = clock_get_alarm_hour_digit(2);
            segstate.digit_nums[2] = clock_get_alarm_minute_digit(1);
            segstate.digit_nums[3] = clock_get_alarm_minute_digit(2);
        }
        else //otherwise just display the normal time
        {
            segstate.digit_nums[0] = clock_get_hour_digit(1);    
            segstate.digit_nums[1] = clock_get_hour_digit(2);
            segstate.digit_nums[2] = clock_get_minute_digit(1);
            segstate.digit_nums[3] = clock_get_minute_digit(2);
        }
        

        //then update the numbers to actual IO port states
        //If first digit (hour) is 0, then don't display
        if (segstate.digit_nums[0] == 0)
        {
            segstate.digit_states[0] = 0x00;
        }
        else
        {
            segstate.digit_states[0] = sevenseg_translate_num_to_state(segstate.digit_nums[0]);
        }
        segstate.digit_states[1] = sevenseg_translate_num_to_state(segstate.digit_nums[1]);
        segstate.digit_states[2] = sevenseg_translate_num_to_state(segstate.digit_nums[2]);
        segstate.digit_states[3] = sevenseg_translate_num_to_state(segstate.digit_nums[3]);
    }
    
}

uint8_t sevenseg_translate_num_to_state(uint8_t num)
{
    uint8_t state; 
    
    if (num < 16)
    {
        state = num_to_segstate[num];
    }
    else
    {
        state = 0xFF;
    }
    
    return state;
}

void sevenseg_update_digit_state()
{
    //first update the current digit and set anode outputs
    segstate.current_dig_num = (segstate.current_dig_num + 1);
    if (segstate.current_dig_num >= 4)
    {
        segstate.current_dig_num = 0;
    }
    segstate.current_dig_state = segstate.digit_states[segstate.current_dig_num];
    IO_SEVENSEG_LED_LAT = segstate.current_dig_state;

    //set the cathode outputs as well
    switch(segstate.current_dig_num)
    {
        case 0:
            IO_LED_DIG1_SetLow();
            IO_LED_DIG2_SetHigh();
            IO_LED_DIG3_SetHigh();
            IO_LED_DIG4_SetHigh();
            break;
        case 1:
            IO_LED_DIG1_SetHigh();
            IO_LED_DIG2_SetLow();
            IO_LED_DIG3_SetHigh();
            IO_LED_DIG4_SetHigh();
            break;
        case 2:
            IO_LED_DIG1_SetHigh();
            IO_LED_DIG2_SetHigh();
            IO_LED_DIG3_SetLow();
            IO_LED_DIG4_SetHigh();
            break;
        case 3:
            IO_LED_DIG1_SetHigh();
            IO_LED_DIG2_SetHigh();
            IO_LED_DIG3_SetHigh();
            IO_LED_DIG4_SetLow();
            break;
        default:
            IO_LED_DIG1_SetLow();
            IO_LED_DIG2_SetHigh();
            IO_LED_DIG3_SetHigh();
            IO_LED_DIG4_SetHigh();
            break;
    }

}
