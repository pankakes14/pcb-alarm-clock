/*
 * File:   main.c
 * Author: Scott
 *
 * Created on April 4, 2018, 8:02 PM
 */


#include "main.h"
#include "config.h"
#include "timer.h"
#include "clock.h"
#include "sevenseg.h"
#include "buttons.h"
#include "RGB.h"
#include "speaker.h"



void main(void) 
{
    SYSTEM_TICKS = 0;
    
    //initialize everything!
    initialize_peripherals();
    enable_interrupts();  
    init_RGB();
    init_sevenseg();
    init_buttons();
    init_speaker();
    
    
    //==================MAIN LOOP=======================
    while(1)
    {
        //Basically just check tasks in order to see whether there is something to do
        
        //update time display
        sevenseg_update_display();
        
        //check whether alarm has occurred
        clock_handle_alarms();
        
        //handle input from the user
        buttons_handle_input();
        
        //update the RGB LED back-lighting 
        RGB_update_LEDs();
        
    }
    
    
}


