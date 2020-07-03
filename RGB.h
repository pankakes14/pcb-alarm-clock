/* 
 * File:   RGB.h
 * Author: Scott
 *
 * Created on April 6, 2018, 10:54 PM
 */

#ifndef RGB_H
#define	RGB_H

#ifdef	__cplusplus
extern "C" 
#endif

#define RGB_REFRESH_PERIOD_MS 10

#define MAX_COLOR_TARGETS 20


//these will define which type of color profile we're dealing with
#define COLORPROFILE_MODE_RANDOM 1 //choose random target values within a min and max
#define COLORPROFILE_MODE_TARGET 2 //run a prespecified color pattern

typedef struct _colorprofile_t
{
    //define how quickly the profile updates
    uint16_t update_period;
    
    uint8_t mode; //defines behavior of the profile. 
    
    //these are only relevant if next target is random
    uint8_t red_start;
    uint8_t green_start;
    uint8_t blue_start;
    uint8_t red_max;
    uint8_t green_max;
    uint8_t blue_max;
    
    //the following allow a specific pattern to be defined
    uint8_t red_target;
    uint8_t green_target;
    uint8_t blue_target;
    
    uint8_t target_index; //current target index
    
    uint8_t red_target_list[MAX_COLOR_TARGETS];
    uint8_t green_target_list[MAX_COLOR_TARGETS];
    uint8_t blue_target_list[MAX_COLOR_TARGETS];
    
    
}colorprofile_t;

colorprofile_t daytime_profile;
colorprofile_t sunset_profile;
colorprofile_t sunrise_profile;
colorprofile_t nighttime_profile;

//main structure that stores the state of all things RGB LED
typedef struct _rgbstatus_t
{
    uint8_t red_brightness;
    uint8_t green_brightness;
    uint8_t blue_brightness;
    uint8_t red_update_ticks;
    uint8_t green_update_ticks;
    uint8_t blue_update_ticks;
    
    uint8_t color_state;
    uint32_t last_tick_time;
    
    uint32_t last_color_update;
    
    colorprofile_t *currentprofle;
    uint8_t red_direction; //the direction variables will be 1 if color is increasing, 0 if decreasing
    uint8_t blue_direction;
    uint8_t green_direction; 
    
} rgbstatus_t;

rgbstatus_t rgbstatus;


void init_RGB();
void RGB_init_patterns();
void RGB_update_LEDs();
void RGB_update_profile(colorprofile_t *profile);
void RGB_test_sequence();
void RGB_update_colors();
void RGB_update_target_profile();
void RGB_update_random_profile();


#ifdef	__cplusplus

#endif

#endif	/* RGB_H */

