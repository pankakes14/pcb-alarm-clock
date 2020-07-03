#include "main.h"
#include "config.h"
#include "speaker.h"



void init_speaker()
{
    speakerstat.alarm_in_progress = 0;
    speakerstat.alarm_snooze_in_progress = 0;
    speakerstat.alarm_snooze_minutes = 8;
    speakerstat.sound_in_progress = 0;
}


void speaker_initiate_alarm()
{   
    speakerstat.alarm_in_progress = 1;
    speakerstat.alarm_snoozed = 0;
    speaker_start_alarm_tone();
}


void speaker_start_alarm_tone()
{
    speaker_on();
    speakerstat.sound_data = ALARM_TONE;
    speakerstat.sound_idx = 0;
    speakerstat.sound_idx_max = ALARM_TONE_NUM_ELEMENTS;
    speakerstat.sound_in_progress = 1;
    
}


void speaker_play_space()
{
    speaker_on();
    speakerstat.sound_data = SPACE;
    speakerstat.sound_idx = 0;
    speakerstat.sound_idx_max = SPACE_NUM_ELEMENTS;
    speakerstat.sound_in_progress = 1;
    
}

void speaker_stop_playing()
{
    speaker_off();
    speakerstat.sound_in_progress = 0;
}


void speaker_on()
{
    T4CONbits.TMR4ON = 1;
    T2CONbits.TMR2ON = 1;
    CCPR1L = 0;
    TMR4IE = 1;
}

void speaker_off()
{
    T4CONbits.TMR4ON = 0;
    T2CONbits.TMR2ON = 0;
    CCPR1L = 0;
}