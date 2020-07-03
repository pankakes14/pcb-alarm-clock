/*
 Scott - interrupts.c
 
 */
#include "main.h"
#include "config.h"
#include "speaker.h"
#include "timer.h"

void main_isr();
void timer0_isr();
void rtc_isr();
void speaker_isr();

void interrupt low_priority low_isr()
{
    main_isr();
}

void interrupt high_isr()
{
    main_isr();
}


void main_isr(void)
{
    // TIMER 0 SYSTEM TICK interrupt
    if (TMR0IF && TMR0IE)
    {
        timer0_isr();
    }
    
    // REAL TIME CLOCK ISR
    if (PIR3bits.RTCCIF)
    {
        rtc_isr();
    }
    
    //PWM update interrupt for speaker
    if (TMR4IF && TMR4IE)
    {
        speaker_isr();
    }
    
    
    
}


void timer0_isr()
{
    TMR0IF = 0;
    
    //init timer 0 so overflow happens in 1ms.
    TMR0H = T0_TMR_VAL_1MS >> 8;
    TMR0L = (T0_TMR_VAL_1MS & 0xFF);
    SYSTEM_TICKS += 1;
}


void rtc_isr()
{
    //alarm has triggered. Beep the thing!
    speaker_initiate_alarm();    
    PIR3bits.RTCCIF = 0;
}


void speaker_isr()
{
    //update the sound clip to the next PCM sample
    if (speakerstat.sound_in_progress)
    {
        
        //update the PWM duty cycle with next sample
        CCPR1L = speakerstat.sound_data[speakerstat.sound_idx];
        speakerstat.sound_idx++;
        
        if (speakerstat.sound_idx >= speakerstat.sound_idx_max)
        {
            speakerstat.sound_in_progress = 0;
            speakerstat.alarm_end_time = timer_get_ticks();
        }
    }
    TMR4IF = 0;
}