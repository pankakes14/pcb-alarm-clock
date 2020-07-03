/*
 Scott clock.c
 
 */
#include "main.h"
#include "clock.h"
#include "config.h"
#include "speaker.h"
#include "timer.h"
#include "buttons.h"


/* MAIN TASK called from main
 
 */
void clock_handle_alarms()
{
    // Repeat alarm logic - if alarm in progress and alarm tone has completed, start tone again
    if (speakerstat.sound_in_progress == 0 && speakerstat.alarm_in_progress == 1 && !speakerstat.alarm_snoozed &&
            timer_has_time_elapsed(speakerstat.alarm_end_time, SPEAKER_MS_WAIT_BEFORE_REPEAT))
    {
        speaker_start_alarm_tone();
    }
    
     
    //SNOOZE logic -
    if (!speakerstat.alarm_in_progress && speakerstat.alarm_snooze_in_progress)
    {
        clock_snooze_stop();
    }
    
    
    //blink LED if alarm in progress
    if (timer_has_time_elapsed(speakerstat.snooze_LED_blink_update_time, 1000) && speakerstat.alarm_in_progress)
    {
        speakerstat.snooze_LED_blink_update_time = timer_get_ticks();
        IO_DEBUG_LED_Toggle();
    }
    else if (speakerstat.alarm_in_progress == 0 && buttstatus.alarm_on_state == 1)
    {
        IO_DEBUG_LED_SetHigh();
    }
    
    
    
}


void clock_set_minute_digit(uint8_t digit, uint8_t minute)
{
    uint8_t temp_rtcval;
    
    RTCCFGbits.RTCWREN = 1; //enable writes to RTC module
    
    //set RTC val to represent minutes
    RTCCFGbits.RTCPTR0 = 0;
    RTCCFGbits.RTCPTR1 = 0;
    
    temp_rtcval = RTCVALH;
    
    if (digit == 1)
    {
        temp_rtcval = temp_rtcval  & 0xF;
        temp_rtcval |= (minute << 4);
    }
    else
    {
        temp_rtcval = temp_rtcval  & 0xF0;
        temp_rtcval |= minute;
    }
    
    //set RTC val to represent minutes
    RTCCFGbits.RTCPTR0 = 0;
    RTCCFGbits.RTCPTR1 = 0;
    RTCVALH = temp_rtcval;
    
}


void clock_set_hour_digit(uint8_t digit, uint8_t hour)
{
    
    uint8_t temp_rtcval;
    
    RTCCUnLock();
    
    //set RTC val to represent hours
    RTCCFGbits.RTCPTR0 = 1;
    RTCCFGbits.RTCPTR1 = 0;
    
    temp_rtcval = RTCVALL;
    
    if (digit == 1)
    {
        temp_rtcval = temp_rtcval  & 0xF;
        temp_rtcval |= (hour << 4);
    }
    else
    {
        temp_rtcval = temp_rtcval  & 0xF0;
        temp_rtcval |= hour;
    }
    
    //set RTC val to represent hours
    RTCCFGbits.RTCPTR0 = 1;
    RTCCFGbits.RTCPTR1 = 0;
    RTCVALL = temp_rtcval;
    
    
    
}

uint8_t clock_get_minute_digit(uint8_t digitnum)
{
    //set RTC val to represent minutes
    RTCCFGbits.RTCPTR0 = 0;
    RTCCFGbits.RTCPTR1 = 0;
    
    //RTCVAL is in binary packed decimal
    if (digitnum == 1)
    {
        return (0x0F & (RTCVALH >> 4));
    }
    else
    {
        return (RTCVALH & 0x0F);
    }
}

uint8_t clock_get_second_digit(uint8_t digitnum)
{
    //set RTC val to represent seconds
    RTCCFGbits.RTCPTR0 = 0;
    RTCCFGbits.RTCPTR1 = 0;
    
    //RTCVAL is in binary packed decimal
    if (digitnum == 1)
    {
        return (0x0F & (RTCVALL >> 4));
    }
    else
    {
        return (RTCVALL & 0x0F);
    }
}


void clock_set_second_digit(uint8_t digit, uint8_t second)
{
    
    uint8_t temp_rtcval;
    
    
    RTCCFGbits.RTCWREN = 1; //enable writes to RTC module
    
    //set RTC val to represent hours
    RTCCFGbits.RTCPTR0 = 0;
    RTCCFGbits.RTCPTR1 = 0;
    
    temp_rtcval = RTCVALL;
    
    if (digit == 1)
    {
        temp_rtcval = temp_rtcval  & 0xF;
        temp_rtcval |= (second << 4);
    }
    else
    {
        temp_rtcval = temp_rtcval  & 0xF0;
        temp_rtcval |= second;
    }
    
    //set RTC val to represent seconds
    RTCCFGbits.RTCPTR0 = 0;
    RTCCFGbits.RTCPTR1 = 0;
    RTCVALL = temp_rtcval;
    
}


uint8_t clock_get_minute()
{
    return (uint8_t)(clock_get_minute_digit(1) * 10 + clock_get_minute_digit(2));
}

uint8_t clock_get_hour()
{
    return (uint8_t)(clock_get_hour_digit(1) * 10 + clock_get_hour_digit(2));
}
        
uint8_t clock_get_hour_digit(uint8_t digitnum)
{
    //set RTC val to represent minutes
    RTCCFGbits.RTCPTR0 = 1;
    RTCCFGbits.RTCPTR1 = 0;
    
    //RTCVAL is in binary packed decimal
    if (digitnum == 1)
    {
        return (0x0F & (RTCVALL >> 4));
    }
    else
    {
        return (RTCVALL & 0x0F);
    }
    
}


//------------------ALARM FUNCTIONS -------------------

void clock_set_alarm_minute_digit(uint8_t digit, uint8_t minute)
{
    uint8_t temp_rtcval;
    
    RTCCFGbits.RTCWREN = 1; //enable writes to RTC module
    
    //set RTC val to represent minutes
    ALRMCFGbits.ALRMPTR0 = 0;
    ALRMCFGbits.ALRMPTR1 = 0;
    
    temp_rtcval = ALRMVALH;
    
    if (digit == 1)
    {
        temp_rtcval = temp_rtcval  & 0xF;
        temp_rtcval |= (minute << 4);
    }
    else
    {
        temp_rtcval = temp_rtcval  & 0xF0;
        temp_rtcval |= minute;
    }
    
    //set RTC val to represent minutes
    ALRMCFGbits.ALRMPTR0 = 0;
    ALRMCFGbits.ALRMPTR1 = 0;
    ALRMVALH = temp_rtcval;
    
}


void clock_set_alarm_hour_digit(uint8_t digit, uint8_t hour)
{
    
    uint8_t temp_rtcval;
    
    RTCCUnLock();
    
    //set RTC val to represent hours
    ALRMCFGbits.ALRMPTR0 = 1;
    ALRMCFGbits.ALRMPTR1 = 0;
    
    temp_rtcval = ALRMVALL;
    
    if (digit == 1)
    {
        temp_rtcval = temp_rtcval  & 0xF;
        temp_rtcval |= (hour << 4);
    }
    else
    {
        temp_rtcval = temp_rtcval  & 0xF0;
        temp_rtcval |= hour;
    }
    
    //set RTC val to represent hours
    ALRMCFGbits.ALRMPTR0 = 1;
    ALRMCFGbits.ALRMPTR1 = 0;
    ALRMVALL = temp_rtcval;
    
    
    
}

uint8_t clock_get_alarm_minute_digit(uint8_t digitnum)
{
    //set RTC val to represent minutes
    ALRMCFGbits.ALRMPTR0 = 0;
    ALRMCFGbits.ALRMPTR1 = 0;
    
    //RTCVAL is in binary packed decimal
    if (digitnum == 1)
    {
        return (0x0F & (ALRMVALH >> 4));
    }
    else
    {
        return (ALRMVALH & 0x0F);
    }
}

uint8_t clock_get_alarm_second_digit(uint8_t digitnum)
{
    //set RTC val to represent seconds
    ALRMCFGbits.ALRMPTR0 = 0;
    ALRMCFGbits.ALRMPTR1 = 0;
    
    //RTCVAL is in binary packed decimal
    if (digitnum == 1)
    {
        return (0x0F & (ALRMVALL >> 4));
    }
    else
    {
        return (ALRMVALL & 0x0F);
    }
}


void clock_set_alarm_second_digit(uint8_t digit, uint8_t second)
{
    
    uint8_t temp_rtcval;
    
    
    RTCCFGbits.RTCWREN = 1; //enable writes to RTC module
    
    //set RTC val to represent hours
    ALRMCFGbits.ALRMPTR0 = 0;
    ALRMCFGbits.ALRMPTR1 = 0;
    
    temp_rtcval = ALRMVALL;
    
    if (digit == 1)
    {
        temp_rtcval = temp_rtcval  & 0xF;
        temp_rtcval |= (second << 4);
    }
    else
    {
        temp_rtcval = temp_rtcval  & 0xF0;
        temp_rtcval |= second;
    }
    
    //set RTC val to represent seconds
    ALRMCFGbits.ALRMPTR0 = 0;
    ALRMCFGbits.ALRMPTR1 = 0;
    ALRMVALL = temp_rtcval;
    
}


uint8_t clock_get_alarm_minute()
{
    return (uint8_t)(clock_get_alarm_minute_digit(1) * 10 + clock_get_alarm_minute_digit(2));
}

uint8_t clock_get_alarm_hour()
{
    return (uint8_t)(clock_get_alarm_hour_digit(1) * 10 + clock_get_alarm_hour_digit(2));
}
        
uint8_t clock_get_alarm_hour_digit(uint8_t digitnum)
{
    //set RTC val to represent minutes
    ALRMCFGbits.ALRMPTR0 = 1;
    ALRMCFGbits.ALRMPTR1 = 0;
    
    //RTCVAL is in binary packed decimal
    if (digitnum == 1)
    {
        return (0x0F & (ALRMVALL >> 4));
    }
    else
    {
        return (ALRMVALL & 0x0F);
    }
    
}




void clock_disable_alarm()
{
    ALRMCFGbits.ALRMEN = 0;
    speakerstat.alarm_in_progress = 0;
    
    if (speakerstat.alarm_snooze_in_progress)
    {
        clock_snooze_stop();
    }
}


void clock_enable_alarm()
{
    ALRMCFGbits.ALRMEN = 1;
}


//change the time by 'increment amount (can be negative number for decreasing)
void clock_increase_time(int increment_amount)
{
    int8_t minute1, minute2, hour1, hour2;
    int8_t minute, hour;
    
      
    minute1 = clock_get_minute_digit(1);
    minute2 = clock_get_minute_digit(2);
    minute = minute1 * 10 + minute2;
    
    //convert the BPD to normal integer
    hour1 = clock_get_hour_digit(1);
    hour2 = clock_get_hour_digit(2);
    hour = hour1 * 10 + hour2;
    
    
    minute = (minute + increment_amount) % 60; //  increment/decrement the minute
    
    //2 cases negative and positive
    if (increment_amount > 0)
    {
        //if minute is 0, increase hour
        if (minute == 0)
        {
            hour = (hour + increment_amount) % 24;
        }
    }
    else //increment_amount negative
    {
        //if minute is -1, we've rolled over from last hour. Make minute 59 and decrease hour
        if (minute == -1)
        {
            minute = 59;
            hour = hour - 1;

        }
        if (hour == -1)
        {
            hour = 23;
        }
    }
    
    
    //convert back to BPD  
    minute1 = minute / 10;
    minute2 = minute % 10;
    hour1 = hour / 10;
    hour2 = hour % 10;
    
    //set new time
    clock_set_minute_digit(1, minute1);
    clock_set_minute_digit(2, minute2);
    clock_set_hour_digit(1, hour1);
    clock_set_hour_digit(2, hour2);
}

//change the time by 'increment amount (can be negative number for decreasing)
void clock_increase_alarm_time(int increment_amount)
{
    int8_t minute1, minute2, hour1, hour2;
    int8_t minute, hour;
    
    
    
    minute1 = clock_get_alarm_minute_digit(1);
    minute2 = clock_get_alarm_minute_digit(2);
    minute = minute1 * 10 + minute2;
    
    //convert the BPD to normal integer
    hour1 = clock_get_alarm_hour_digit(1);
    hour2 = clock_get_alarm_hour_digit(2);
    hour = hour1 * 10 + hour2;
    
    minute = (minute + increment_amount) % 60; //  increment/decrement the minute
    
    //2 cases negative and positive
    if (increment_amount > 0)
    {
        //if minute is 0, increase hour
        if (minute == 0)
        {
            hour = (hour + increment_amount) % 24;
        }
    }
    else //increment_amount negative
    {
        //if minute is -1, we've rolled over from last hour. Make minute 59 and decrease hour
        if (minute == -1)
        {
            minute = 59;
            hour = hour - 1;

        }
        if (hour == -1)
        {
            hour = 23;
        }
    }
    
    //convert back to BPD  
    minute1 = minute / 10;
    minute2 = minute % 10;
    hour1 = hour / 10;
    hour2 = hour % 10;
    
    //set new time
    clock_set_alarm_minute_digit(1, minute1);
    clock_set_alarm_minute_digit(2, minute2);
    clock_set_alarm_hour_digit(1, hour1);
    clock_set_alarm_hour_digit(2, hour2);
}

void clock_snooze_alarm()
{
    //don't do anything if alarm is not in progress
    if (speakerstat.alarm_in_progress)
    {
        //stop the alarm
        speaker_stop_playing();
        speakerstat.alarm_snoozed = 1;
        
        
        //only update the original snooze time if we're not already snoozing
        if (!speakerstat.alarm_snooze_in_progress)
        {
            speakerstat.alarm_snooze_in_progress = 1;
            //record the minute and hour that the snooze started so that we can restore it later 
            speakerstat.alarm_snooze_minute = clock_get_alarm_minute();
            speakerstat.alarm_snooze_hour = clock_get_alarm_hour();
        }
        
        //re-set the alarm for later time
        clock_increase_alarm_time(speakerstat.alarm_snooze_minutes);
    }
}

void clock_snooze_stop()
{
    int8_t minute1, minute2, hour1, hour2;
    
    speakerstat.alarm_snooze_in_progress = 0;
    speakerstat.alarm_snoozed = 0;
    speaker_stop_playing();
    
    //convert back to BPD  
    minute1 = speakerstat.alarm_snooze_minute / 10;
    minute2 = speakerstat.alarm_snooze_minute % 10;
    hour1 = speakerstat.alarm_snooze_hour / 10;
    hour2 = speakerstat.alarm_snooze_hour % 10;
    
    //set new time
    clock_set_alarm_minute_digit(1, minute1);
    clock_set_alarm_minute_digit(2, minute2);
    clock_set_alarm_hour_digit(1, hour1);
    clock_set_alarm_hour_digit(2, hour2);
}