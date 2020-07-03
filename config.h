/* 
 * File:   config.h
 * Author: Scott
 *
 * Created on April 4, 2018, 8:03 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" 
#endif

//TIMER 0
#define T0_TICKS_PER_MS 750
#define T0_TMR_VAL_1MS 0xFD11
    
//define lock and unlock macros for RTCC
#define  IOUnLock() do {EECON2 = 0x55; EECON2 = 0xAA; PPSCONbits.IOLOCK = 0;} while (0)
#define  IOLock()   PPSCONbits.IOLOCK=1
    
//===============RTC SECTION=========================
//clock measured 16 seconds slow over the course of ~8 days which is .0023% error
//.0023% error of 32,768 is .7487 * 60 = ~45 RTC ticks per minute
#define RTC_CAL_VALUE 45
    
    
//==============GPIO PIN ASSIGNMENTS=================
    
#define IO_DEBUG_LED_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define IO_DEBUG_LED_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define IO_DEBUG_LED_Toggle()             do { LATAbits.LATA6 ^= 1; } while(0)
#define IO_DEBUG_LED_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
    
    
//7 - seg LED pins
#define IO_SEVENSEG_LED_LAT         LATB
#define IO_SEVENSEG_DP_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define IO_SEVENSEG_DP_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define IO_SEVENSEG_DP_SetLow()             do { LATDbits.LATD4 = 0; } while(0)

#define IO_LED_A_TRIS               TRISBbits.TRISB0
#define IO_LED_A_LAT                LATBbits.LATB0
#define IO_LED_A_ANS                ANSELBbits.ANSB0
#define IO_LED_A_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define IO_LED_A_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define IO_LED_A_Toggle()             do { LATBbits.LATB0 ^= 1; } while(0)
#define IO_LED_A_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define IO_LED_A_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)

#define IO_LED_B_TRIS               TRISBbits.TRISB1
#define IO_LED_B_LAT                LATBbits.LATB1
#define IO_LED_B_ANS                ANSELBbits.ANSB1
#define IO_LED_B_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define IO_LED_B_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define IO_LED_B_Toggle()             do { LATBbits.LATB1 ^= 1; } while(0)
#define IO_LED_B_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define IO_LED_B_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)

#define IO_LED_C_TRIS               TRISBbits.TRISB2
#define IO_LED_C_LAT                LATBbits.LATB2
#define IO_LED_C_ANS                ANSELBbits.ANSB2
#define IO_LED_C_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define IO_LED_C_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define IO_LED_C_Toggle()             do { LATBbits.LATB2 ^= 1; } while(0)
#define IO_LED_C_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define IO_LED_C_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)

#define IO_LED_D_TRIS               TRISBbits.TRISB3
#define IO_LED_D_LAT                LATBbits.LATB3
#define IO_LED_D_ANS                ANSELBbits.ANSB3
#define IO_LED_D_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define IO_LED_D_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define IO_LED_D_Toggle()             do { LATBbits.LATB3 ^= 1; } while(0)
#define IO_LED_D_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define IO_LED_D_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)

#define IO_LED_E_TRIS               TRISBbits.TRISB4
#define IO_LED_E_LAT                LATBbits.LATB4
#define IO_LED_E_ANS                ANSELBbits.ANSB4
#define IO_LED_E_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_LED_E_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_LED_E_Toggle()             do { LATBbits.LATB4 ^= 1; } while(0)
#define IO_LED_E_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_LED_E_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)

#define IO_LED_F_TRIS               TRISBbits.TRISB5
#define IO_LED_F_LAT                LATBbits.LATB5
#define IO_LED_F_ANS                ANSELBbits.ANSB5
#define IO_LED_F_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define IO_LED_F_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define IO_LED_F_Toggle()             do { LATBbits.LATB5 ^= 1; } while(0)
#define IO_LED_F_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define IO_LED_F_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)

#define IO_LED_G_TRIS               TRISBbits.TRISB6
#define IO_LED_G_LAT                LATBbits.LATB6
#define IO_LED_G_ANS                ANSELBbits.ANSB6
#define IO_LED_G_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define IO_LED_G_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define IO_LED_G_Toggle()             do { LATBbits.LATB6 ^= 1; } while(0)
#define IO_LED_G_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define IO_LED_G_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)

#define IO_LED_DP_TRIS               TRISBbits.TRISB7
#define IO_LED_DP_LAT                LATBbits.LATB7
#define IO_LED_DP_ANS                ANSELBbits.ANSB7
#define IO_LED_DP_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define IO_LED_DP_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define IO_LED_DP_Toggle()             do { LATBbits.LATB7 ^= 1; } while(0)
#define IO_LED_DP_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define IO_LED_DP_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
    
#define IO_LED_DIG1_TRIS               TRISCbits.TRISC2
#define IO_LED_DIG1_LAT                LATCbits.LATC2
#define IO_LED_DIG1_ANS                ANSELCbits.ANSC2
#define IO_LED_DIG1_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define IO_LED_DIG1_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define IO_LED_DIG1_Toggle()             do { LATCbits.LATC2 ^= LATCbits.LATC2; } while(0)
#define IO_LED_DIG1_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define IO_LED_DIG1_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
    
#define IO_LED_DIG2_TRIS               TRISBbits.TRISB7
#define IO_LED_DIG2_LAT                LATBbits.LATB7
#define IO_LED_DIG2_ANS                ANSELDbits.ANSB7
#define IO_LED_DIG2_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define IO_LED_DIG2_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define IO_LED_DIG2_Toggle()             do { LATBbits.LATB7 ^= LATBbits.LATB7; } while(0)
#define IO_LED_DIG2_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define IO_LED_DIG2_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
    
#define IO_LED_DIG3_TRIS               TRISCbits.TRISC6
#define IO_LED_DIG3_LAT                LATCbits.LATC6
#define IO_LED_DIG3_ANS                ANSELCbits.ANSC6
#define IO_LED_DIG3_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define IO_LED_DIG3_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define IO_LED_DIG3_Toggle()             do { LATCbits.LATC6 ^= 1; } while(0)
#define IO_LED_DIG3_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define IO_LED_DIG3_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
    
#define IO_LED_DIG4_TRIS               TRISCbits.TRISC7
#define IO_LED_DIG4_LAT                LATCbits.LATC7
#define IO_LED_DIG4_ANS                ANSELCbits.ANSC7
#define IO_LED_DIG4_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define IO_LED_DIG4_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define IO_LED_DIG4_Toggle()             do { LATCbits.LATC7 ^= 1; } while(0)
#define IO_LED_DIG4_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define IO_LED_DIG4_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
    
    
//-------now set up button inputs
#define IO_SET_ALARM_TIME_TRIS               TRISAbits.TRISA3
#define IO_SET_ALARM_TIME_LAT                LATAbits.LATA3
#define IO_SET_ALARM_TIME_ANS                ANSELAbits.ANSA0
#define IO_SET_ALARM_TIME_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define IO_SET_ALARM_TIME_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define IO_SET_ALARM_TIME_Toggle()             do { LATAbits.LATA3 ^= 1; } while(0)
#define IO_SET_ALARM_TIME_GetValue()           PORTAbits.RA3
#define IO_SET_ALARM_TIME_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define IO_SET_ALARM_TIME_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
   
#define IO_TIME_UP_TRIS               TRISAbits.TRISA0
#define IO_TIME_UP_LAT                LATAbits.LATA0
#define IO_TIME_UP_ANS                ANSELAbits.ANSA0
#define IO_TIME_UP_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define IO_TIME_UP_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define IO_TIME_UP_Toggle()             do { LATAbits.LATA0 ^= 1; } while(0)
#define IO_TIME_UP_GetValue()           PORTAbits.RA0
#define IO_TIME_UP_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define IO_TIME_UP_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)

#define IO_TIME_DOWN_TRIS               TRISAbits.TRISA2
#define IO_TIME_DOWN_LAT                LATAbits.LATA2
#define IO_TIME_DOWN_ANS                ANSELAbits.ANSA2
#define IO_TIME_DOWN_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define IO_TIME_DOWN_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define IO_TIME_DOWN_Toggle()             do { LATAbits.LATA2 ^= 1; } while(0)
#define IO_TIME_DOWN_GetValue()           PORTAbits.RA2
#define IO_TIME_DOWN_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define IO_TIME_DOWN_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
    
#define IO_SNOOZE_TRIS               TRISAbits.TRISA5
#define IO_SNOOZE_LAT                LATAbits.LATA5
#define IO_SNOOZE_ANS                ANSELAbits.ANSA5
#define IO_SNOOZE_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define IO_SNOOZE_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define IO_SNOOZE_Toggle()             do { LATAbits.LATA5 ^= 1; } while(0)
#define IO_SNOOZE_GetValue()           PORTAbits.RA5
#define IO_SNOOZE_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define IO_SNOOZE_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
 
#define IO_ALARM_STATE_TRIS               TRISEbits.TRISA0
#define IO_ALARM_STATE_LAT                LATEbits.LATE0
#define IO_ALARM_STATE_ANS                ANSELEbits.ANSA0
#define IO_ALARM_STATE_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define IO_ALARM_STATE_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define IO_ALARM_STATE_Toggle()             do { LATEbits.LATE0 ^= 1; } while(0)
#define IO_ALARM_STATE_GetValue()           PORTEbits.RE0
#define IO_ALARM_STATE_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define IO_ALARM_STATE_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
    
//-------set up RGB LED outputs
#define IO_RGB_RED_TRIS               TRISDbits.TRISD0
#define IO_RGB_RED_LAT                LATDbits.LATD0
#define IO_RGB_RED_ANS                ANSELDbits.ANSD0
#define IO_RGB_RED_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define IO_RGB_RED_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define IO_RGB_RED_Toggle()             do { LATDbits.LATD0 ^= 1; } while(0)
#define IO_RGB_RED_SetDigitalInput()    do { TRISbits.TRISD0 = 1; } while(0)
#define IO_RGB_RED_SetDigitalOutput()   do { TRISBbits.TRISD0 = 0; } while(0)

#define IO_RGB_GREEN_TRIS               TRISDbits.TRISD1
#define IO_RGB_GREEN_LAT                LATDbits.LATD1
#define IO_RGB_GREEN_ANS                ANSELDbits.ANSD1
#define IO_RGB_GREEN_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define IO_RGB_GREEN_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define IO_RGB_GREEN_Toggle()             do { LATDbits.LATD1 ^= 1; } while(0)
#define IO_RGB_GREEN_SetDigitalInput()    do { TRISbits.TRISD1 = 1; } while(0)
#define IO_RGB_GREEN_SetDigitalOutput()   do { TRISBbits.TRISD1 = 0; } while(0)
       
#define IO_RGB_BLUE_TRIS               TRISDbits.TRISD2
#define IO_RGB_BLUE_LAT                LATDbits.LATD2
#define IO_RGB_BLUE_ANS                ANSELDbits.ANSD2
#define IO_RGB_BLUE_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define IO_RGB_BLUE_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define IO_RGB_BLUE_Toggle()             do { LATDbits.LATD2 ^= 1; } while(0)
#define IO_RGB_BLUE_SetDigitalInput()    do { TRISbits.TRISD2 = 1; } while(0)
#define IO_RGB_BLUE_SetDigitalOutput()   do { TRISBbits.TRISD2 = 0; } while(0)
    
    

    
//functions
void initialize_peripherals();
void enable_interrupts();
void init_osc();
void init_timers();
void init_GPIO();
void init_RTC();
void init_PWM();


#ifdef	__cplusplus

#endif

#endif	/* CONFIG_H */

