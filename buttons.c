/*
 Scott clock.c
 
 */
#include "main.h"
#include "config.h"
#include "timer.h"
#include "buttons.h"
#include "clock.h"
#include "speaker.h"


/*  Main Task
 * 
 */
void buttons_handle_input()
{    
    //only update button status periodically - don't check it too fast for debouncing
    if ( timer_has_time_elapsed(buttstatus.time_last_update, BUTTON_DEBOUNCE_PERIOD))
    {
        buttstatus.time_last_update = timer_get_ticks();
        uint8_t tempIO;
        
        //check if buttons pressed
        tempIO = IO_TIME_UP_GetValue();
        if (tempIO == 0 && buttstatus.time_up_prev_state == 1)
        {
            buttstatus.time_up_pressed = 1; 
            buttstatus.time_up_pressed_time = timer_get_ticks();
            buttstatus.time_up_held = 0;
        }
        else if ( (tempIO == 1 && buttstatus.time_up_prev_state == 0) ||
                (tempIO == 1 && buttstatus.time_up_prev_state == 1))
        {
            buttstatus.time_up_pressed = 0; 
            buttstatus.time_up_held = 0;
            buttstatus.time_up_pressed_time = 0;
        }
        if ((buttstatus.time_up_pressed_time != 0) && timer_has_time_elapsed(buttstatus.time_up_pressed_time, BUTTON_HOLD_TIME))
        {
            buttstatus.time_up_pressed_time = 0;
            buttstatus.time_up_held = 1;
        }
        
        //time down button
        tempIO = IO_TIME_DOWN_GetValue();
        if (tempIO == 0 && buttstatus.time_down_prev_state == 1)
        {
            buttstatus.time_down_pressed = 1; 
            buttstatus.time_down_pressed_time = timer_get_ticks();
            buttstatus.time_down_held = 0;
        }
        else if ( (tempIO == 1 && buttstatus.time_down_prev_state == 0) ||
                (tempIO == 1 && buttstatus.time_down_prev_state == 1))
        {
            buttstatus.time_down_pressed = 0;
            buttstatus.time_down_held = 0;
            buttstatus.time_down_pressed_time = 0;
        }
        if ((buttstatus.time_down_pressed_time != 0) && timer_has_time_elapsed(buttstatus.time_down_pressed_time, BUTTON_HOLD_TIME))
        {
            buttstatus.time_down_pressed_time = 0;
            buttstatus.time_down_held = 1;
        }
        
        
        //set alarm time button
        tempIO = IO_SET_ALARM_TIME_GetValue();
        if (tempIO == 0 && buttstatus.set_alarm_time_prev_state == 1)
        {
            buttstatus.set_alarm_time_pressed = 1;
        }
        else if ((tempIO == 1 && buttstatus.set_alarm_time_prev_state == 1))
        {
            buttstatus.set_alarm_time_pressed = 0; 
        }
        
        tempIO = IO_SNOOZE_GetValue();
        if (tempIO == 0 && buttstatus.snooze_prev_state == 1)
        {
            buttstatus.snooze_pressed = 1;
            buttstatus.snooze_pressed_time = timer_get_ticks();
            buttstatus.snooze_held = 0;
        }
        else if ( (tempIO == 1 && buttstatus.snooze_prev_state == 0) ||
                (tempIO == 1 && buttstatus.snooze_prev_state == 1))
        {
            buttstatus.snooze_pressed = 0;
            buttstatus.snooze_held = 0;
            buttstatus.snooze_pressed_time = 0;
        }
        if ((buttstatus.snooze_pressed_time != 0) && timer_has_time_elapsed(buttstatus.snooze_pressed_time, SNOOZE_HOLD_TIME))
        {
            buttstatus.snooze_pressed_time = 0;
            buttstatus.snooze_held = 1;
        }
        
        
        
        //next, update previous states
        buttstatus.time_up_prev_state = IO_TIME_UP_GetValue();
        buttstatus.time_down_prev_state = IO_TIME_DOWN_GetValue();
        buttstatus.set_alarm_time_prev_state = IO_SET_ALARM_TIME_GetValue();
        buttstatus.snooze_prev_state = IO_SNOOZE_GetValue();
        
        //don't need to debounce this alarm on off switch. Just get value
        buttstatus.alarm_on_state = !IO_ALARM_STATE_GetValue();
    }
    
    //next perform actions based on which buttons are pressed
    buttons_take_action();
    
}

void init_buttons()
{
    buttstatus.time_last_update = timer_get_ticks();
    buttstatus.time_last_action_update = timer_get_ticks();
    buttstatus.snooze_pressed = 0;
    buttstatus.time_up_pressed = 0;
    buttstatus.time_down_pressed = 0;
    buttstatus.set_alarm_time_pressed = 0;
    buttstatus.alarm_on_state = 0;
    
    buttstatus.time_up_prev_state = IO_TIME_UP_GetValue();
    buttstatus.time_down_prev_state = IO_TIME_DOWN_GetValue();
    buttstatus.set_alarm_time_prev_state = IO_SET_ALARM_TIME_GetValue();
    buttstatus.snooze_prev_state = IO_SNOOZE_GetValue();
    
}


void buttons_take_action()
{
    
    if (timer_has_time_elapsed(buttstatus.time_last_action_update, TIME_UPDATE_PERIOD))
    {
        buttstatus.time_last_action_update = timer_get_ticks();
    
    
        //if time up button pressed and alarm set button not pressed
        if ( !buttstatus.set_alarm_time_pressed && (buttstatus.time_up_pressed || buttstatus.time_up_held) )
        {   
            buttstatus.time_up_pressed = 0;
            clock_increase_time(1); //increase time by 1 minute
        }

        //if down button pressed and alarm set button not pressed
        if ( !buttstatus.set_alarm_time_pressed && (buttstatus.time_down_pressed || buttstatus.time_down_held) )
        {
            buttstatus.time_down_pressed = 0;
            clock_increase_time(-1); //decrease time by 1 minute
        }

        //if up button pressed and alarm set button pressed change alarm time
        if ( buttstatus.set_alarm_time_pressed && (buttstatus.time_up_pressed || buttstatus.time_up_held) )
        {
            buttstatus.time_up_pressed = 0;
            clock_increase_alarm_time(1);
        }

        //if down button pressed and alarm set button pressed change alarm time
        if ( buttstatus.set_alarm_time_pressed && (buttstatus.time_down_pressed || buttstatus.time_down_held) )
        {
            buttstatus.time_down_pressed = 0;
            clock_increase_alarm_time(-1);
        }
        
        //stop alarm logic - if set alarm time is pressed stop alarm until next day
        if (buttstatus.set_alarm_time_pressed)
        {
            speakerstat.alarm_in_progress = 0;
            speaker_stop_playing();
            
            if (speakerstat.alarm_snooze_in_progress)
            {
                clock_snooze_stop();
            }
        }
    

        //if snooze pressed snooze the alarm 
        if ( buttstatus.snooze_pressed )
        {
            clock_snooze_alarm();
            buttstatus.snooze_pressed = 0;
        }
        //if snooze button held, play the secret space sound spaaaaaaaaceee!!!
        if ( buttstatus.snooze_held)
        {
            if (!speakerstat.sound_in_progress)
            {
                speaker_play_space();
            }
        }

        //turn alarm on if switch is set otherwise turn it off
        if ( buttstatus.alarm_on_state )
        {
            //don't set the LED if alarm is in progress as it should be flashing
            if (!speakerstat.alarm_in_progress)
            {
                IO_DEBUG_LED_SetHigh();
            }
            clock_enable_alarm();
        }
        else
        {
            clock_disable_alarm();
            IO_DEBUG_LED_SetLow();
        }
    }
}