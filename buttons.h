/* 
 * File:   buttons.h
 * Author: Scott
 *
 * Created on April 6, 2018, 10:53 PM
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" 
#endif

#define BUTTON_DEBOUNCE_PERIOD 25
#define TIME_UPDATE_PERIOD 12
#define BUTTON_HOLD_TIME 550
#define SNOOZE_HOLD_TIME 3000

typedef struct _buttstatus_t
{
    uint32_t time_last_update;
    uint32_t time_up_pressed_time;
    uint32_t time_down_pressed_time;
    uint32_t snooze_pressed_time;
    
    //prev states for button debouncing
    uint8_t time_up_prev_state;
    uint8_t time_down_prev_state;
    uint8_t snooze_prev_state;
    uint8_t set_alarm_time_prev_state;
    
    //1 if each button is being pressed
    uint8_t time_up_pressed;
    uint8_t time_down_pressed;
    uint8_t snooze_pressed;
    uint8_t set_alarm_time_pressed;
    
    //1 if each button is being held down (pressed for more than 1 second)
    uint32_t time_last_action_update;
    uint8_t time_up_held;
    uint8_t time_down_held;
    uint8_t snooze_held;
   
    uint8_t alarm_on_state;
   
} buttstatus_t;

buttstatus_t buttstatus; //hehehehe

void buttons_handle_input();
void init_buttons();
void buttons_take_action();

#ifdef	__cplusplus

#endif

#endif	/* BUTTONS_H */

