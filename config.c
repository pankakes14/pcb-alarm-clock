/* 
 * File:   config.c
 * Author: Scott
 *
 * Created on April 4, 2018, 8:03 PM
 */


#include <pic18f46j50.h>

#include "main.h"
#include "config.h"
#include "clock.h"



//initialize all of the peripherals
void initialize_peripherals()
{
    //init oscillator
    init_osc();
    
    //init timers
    init_timers();
    
    //init GPIO
    init_GPIO();
    
    //init real time clk
    init_RTC();
    
    //init the PWM module for speaker output
    init_PWM();
    
}

void enable_interrupts()
{
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
}


//initialize oscillator to 48MHz system clk
void init_osc()
{
    OSCCONbits.SCS = 0; //select PLL output
    OSCTUNEbits.PLLEN = 1;
    
    //wait for clk to stablize
    while (OSCCONbits.OSTS == 0);
}


void init_timers()
{
    //setup timer 0 to be system tick clock
    T0CONbits.T0PS = 3; //64 timer prescalar = 1.333uS per tick
    T0CONbits.T0CS = 0; //use FOSC / 4 as clk source
    T0CONbits.T08BIT = 0; //16 bit counter
    T0CONbits.PSA = 0; //don't bypass prescalar
    TMR0H = T0_TMR_VAL_1MS >> 8;
    TMR0L = T0_TMR_VAL_1MS & 0xFF;
    T0CONbits.TMR0ON = 1;
    INTCONbits.T0IE = 1;
    
    //setup timer 1 which will drive RTC
    T1CONbits.T1OSCEN = 1; // enable crystal
    
    //setup timer 2 to go with the PWM module 12MHz clock
    T2CONbits.T2CKPS = 0x0; //no pre/post scalar timer rate = 12MHz
    T2CONbits.T2OUTPS = 0x0;
    T2CONbits.TMR2ON = 1;
    
    //setup timer 4 to tick at 8kHz increments to update the sound bytes
    //this is the sampling frequency of the wav files I'm playing
    T4CONbits.T4CKPS = 3; //1:16 prescale = 750kHz clock
    T4CONbits.T4OUTPS = 0;
    T4CONbits.TMR4ON = 1;
    PR4 = 94; //should interrupt every 1/8kHz
    TMR4IE = 0; //disable interrupt for now
}


void init_GPIO()
{
       
    //make sure USB is disabled and pull ups disabled
    UCONbits.USBEN = 0;
    UCFGbits.UPUEN = 0; //disable pull ups on RC4/5
    ANCON0 = 0xFF;     //disable all analog input
    
    //first initialize 7-seg LED outputs
    TRISB = 0; //all segment LEDs as outputs
    IO_SEVENSEG_DP_SetDigitalOutput();
    IO_SEVENSEG_DP_SetLow();
    IO_LED_DIG1_SetDigitalOutput();
    IO_LED_DIG2_SetDigitalOutput();
    IO_LED_DIG3_SetDigitalOutput();
    IO_LED_DIG4_SetDigitalOutput();
    
    
    //set all button pins to inputs
    TRISA = 0xFF;
    
    //set debug LED to output
    IO_DEBUG_LED_SetDigitalOutput();
    IO_DEBUG_LED_SetLow();
    
    //set all RGB LEDs and speaker to outputs
    TRISD = 0;
    
    //debug LED setup
    IO_DEBUG_LED_SetDigitalOutput();
    IO_DEBUG_LED_SetLow();
}


void init_RTC()
{
    RTCCUnLock(); //enable writes to RTC
    RTCCFGbits.RTCEN = 1; //enable RTC
    
   
    //set crystal calibration
    RTCCAL = RTC_CAL_VALUE;
    
    //set default time to 12:00pm
    clock_set_minute_digit(1, 0);
    clock_set_minute_digit(2, 0);
    clock_set_hour_digit(1, 1);
    clock_set_hour_digit(2, 2);
    clock_set_second_digit(1, 0);
    clock_set_second_digit(2, 0);
    
    //set default alarm time to 12:00pm as well
    clock_set_alarm_minute_digit(1, 0);
    clock_set_alarm_minute_digit(2, 0);
    clock_set_alarm_hour_digit(1, 1);
    clock_set_alarm_hour_digit(2, 2);
    clock_set_alarm_second_digit(1, 0);
    clock_set_alarm_second_digit(2, 0);
    
    //configure the alarm
    ALRMCFGbits.AMASK = 6; //alarm must only match the hour/minute/second fields to trigger
    ALRMCFGbits.CHIME = 1; //allow alarm to repeat for indefinite number of days
    clock_enable_alarm();
   
}

void init_PWM()
{
    IOUnLock(); //unlock access to Peripheral pin select regs
    RPOR20 = 14; //set RP20 (RD3 speaker output) to CCP1 (PWM module) control)
    
    CCP1CONbits.CCP1M = 0xC; //PWM mode all active high
    
     //PWM period to 1/48kHz 
    PR2 = 249;
    CCPR1L = 0; //initialize PWM duty cycle to 0 to set output low

}