/*
 Scott clock.c
 
 */
#include "main.h"
#include "config.h"
#include "timer.h"
#include "RGB.h"
#include "clock.h"
#include "util.h"
#include "speaker.h"



void RGB_update_LEDs()
{
    
    
    //every loop through, update the "update_ticks" until it overflows. 
    //each color LED only stays on for the 'brightness' number of update_ticks.
    //That way it kind of implements PWM in software. 
    rgbstatus.red_update_ticks++;
    rgbstatus.green_update_ticks++;
    rgbstatus.blue_update_ticks++;
    
    //if we've rolled over, turn all LEDs on (stagger turning on so inrush isn't so bad)
    if (rgbstatus.red_update_ticks == 0 && rgbstatus.red_brightness != 0)
    {
        IO_RGB_RED_SetHigh();
    }    
    if (rgbstatus.green_update_ticks == 0 && rgbstatus.green_brightness != 0)
    {
        IO_RGB_GREEN_SetHigh();
    }
    if (rgbstatus.blue_update_ticks == 0 && rgbstatus.blue_brightness != 0)
    {
        IO_RGB_BLUE_SetHigh();
    }
        
    
    //check all LEDs brightness levels to see whether they should turn off this cycle
    if (rgbstatus.red_update_ticks > rgbstatus.red_brightness)
    {
        IO_RGB_RED_SetLow();
    }
    if (rgbstatus.green_update_ticks > rgbstatus.green_brightness)
    {
        IO_RGB_GREEN_SetLow();
    }
    if (rgbstatus.blue_update_ticks > rgbstatus.blue_brightness)
    {
        IO_RGB_BLUE_SetLow();
    }
    
    
    RGB_update_colors();
}

void RGB_init_patterns()
{
    //daytime profile - bright profile that treats all colors equally, and randomly
    //  chooses a target color
    daytime_profile.update_period = 50;    
    daytime_profile.mode = COLORPROFILE_MODE_RANDOM;
    daytime_profile.red_start = 0x0;
    daytime_profile.green_start = 0x0;
    daytime_profile.blue_start = 0x0;
    daytime_profile.red_max = 0xFF;
    daytime_profile.green_max = 0xFF;
    daytime_profile.blue_max = 0xFF;

              
    //sunset profile
    sunset_profile.update_period = 25; 
    sunset_profile.mode = COLORPROFILE_MODE_RANDOM;
    sunset_profile.red_start = 0x60;
    sunset_profile.green_start = 0x40;
    sunset_profile.blue_start = 0x00;
    sunset_profile.red_max = 0xFF;
    sunset_profile.green_max = 0xDD;
    sunset_profile.blue_max = 0x40;
    
    //sunrise profile
    sunrise_profile.update_period = 25; 
    sunrise_profile.mode = COLORPROFILE_MODE_RANDOM;
    sunrise_profile.red_start = 0xCC;
    sunrise_profile.green_start = 0x99;
    sunrise_profile.blue_start = 0x00;
    sunrise_profile.red_max = 0xFF;
    sunrise_profile.green_max = 0xDD;
    sunrise_profile.blue_max = 0x30;
    
    //night time profile
    nighttime_profile.update_period = 25; 
    nighttime_profile.mode = COLORPROFILE_MODE_RANDOM;
    nighttime_profile.red_start = 0x0;
    nighttime_profile.green_start = 0x0;
    nighttime_profile.blue_start = 0x0;
    nighttime_profile.red_max = 0x0;
    nighttime_profile.green_max = 0x0;
    nighttime_profile.blue_max = 0x0;

    
    //alarm profile
}


void RGB_update_profile(colorprofile_t *profile)
{
    rgbstatus.currentprofle = profile;
}


void init_RGB()
{
    rgbstatus.red_brightness = 0;
    rgbstatus.green_brightness = 0;
    rgbstatus.blue_brightness = 255;
    
    //make the update ticks out of phase so that there isn't a huge inrush every update period
    rgbstatus.red_update_ticks = 0;
    rgbstatus.green_update_ticks = 84;
    rgbstatus.blue_update_ticks = 169;
    
    rgbstatus.last_tick_time = timer_get_ticks();
    
    
    RGB_init_patterns();
    RGB_update_profile(&daytime_profile);
    rgbstatus.last_color_update = timer_get_ticks();
    
}



void RGB_test_sequence()
{
    uint8_t seed;
    
    //update colors semi-randomly every 100ms
    if ( timer_has_time_elapsed(rgbstatus.last_color_update, 50) )
    {
        rgbstatus.last_color_update = timer_get_ticks();
        
        seed = get_rand_num(0,25, TMR0L+3);
        rgbstatus.red_brightness += seed;
        seed = get_rand_num(0,25, seed);
        rgbstatus.red_brightness -= seed;
        seed = get_rand_num(0,25, seed);
        rgbstatus.green_brightness += seed;
        seed = get_rand_num(0,25, seed);
        rgbstatus.green_brightness -= seed;
        seed = get_rand_num(0,25, seed);
        rgbstatus.blue_brightness += seed;    
        seed = get_rand_num(0,25, seed);
        rgbstatus.blue_brightness -= seed;

    }
}



void RGB_update_random_profile()
{
    uint8_t seed;
    
    //first check whether we're done
    if (rgbstatus.currentprofle->blue_target == rgbstatus.blue_brightness &&
            rgbstatus.currentprofle->red_target == rgbstatus.red_brightness &&
            rgbstatus.currentprofle->green_target == rgbstatus.green_brightness)
    {
        //generate new target colors
        seed = clock_get_second_digit(2);
        seed = get_rand_num(rgbstatus.currentprofle->red_start, rgbstatus.currentprofle->red_max, seed);
        rgbstatus.currentprofle->red_target = seed;
        
        seed = get_rand_num(rgbstatus.currentprofle->green_start, rgbstatus.currentprofle->green_max, seed);
        rgbstatus.currentprofle->green_target = seed;
        
        seed = get_rand_num(rgbstatus.currentprofle->blue_start, rgbstatus.currentprofle->blue_max, seed);
        rgbstatus.currentprofle->blue_target = seed;
    }
    
    
    //otherwise update colors until they get to their target
    
    //RED
    if (rgbstatus.red_brightness < rgbstatus.currentprofle->red_target)
    {
        rgbstatus.red_brightness++;
    }
    else if (rgbstatus.red_brightness > rgbstatus.currentprofle->red_target)
    {
        rgbstatus.red_brightness--;
    }
    
    //GREEN
    if (rgbstatus.green_brightness < rgbstatus.currentprofle->green_target)
    {
        rgbstatus.green_brightness++;
    }
    else if (rgbstatus.green_brightness > rgbstatus.currentprofle->green_target)
    {
        rgbstatus.green_brightness--;
    }
    
    //BLUE
    if (rgbstatus.blue_brightness < rgbstatus.currentprofle->blue_target)
    {
        rgbstatus.blue_brightness++;
    }
    else if (rgbstatus.blue_brightness > rgbstatus.currentprofle->blue_target)
    {
        rgbstatus.blue_brightness--;
    }
    
}

void RGB_update_target_profile()
{
    
}

//this function is responsible for actually updating the color brightnesses
void RGB_update_colors()
{
    uint8_t hour;
    //RGB_test_sequence();
    
    //only update the colors every 'profile update' period
    if (timer_has_time_elapsed(rgbstatus.last_color_update, rgbstatus.currentprofle->update_period))
    {
        rgbstatus.last_color_update = timer_get_ticks();
        
        if (rgbstatus.currentprofle->mode == COLORPROFILE_MODE_RANDOM)
        {
            RGB_update_random_profile();
        }
        else
        {
            RGB_update_target_profile();
        }
        
        
        
        
        //while we're here, check to see which profile we should be using
        hour = clock_get_hour();
        if (hour >= 10 && hour <= 16)
        {
            RGB_update_profile(&daytime_profile);
        }
        else if (hour >= 17 && hour <= 19)
        {
            RGB_update_profile(&sunset_profile);
        }
        else
        {
            RGB_update_profile(&nighttime_profile);
        }
        
        if (speakerstat.alarm_in_progress)
        {
            RGB_update_profile(&sunrise_profile);
        }
            
    }
}
