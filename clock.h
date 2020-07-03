/* 
 * File:   clock.h
 * Author: Scott
 *
 * Created on April 5, 2018, 9:47 PM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#ifdef	__cplusplus
extern "C" 
#endif

#define RTC_VALH_MINUTES 0
#define RTC_VALL_SECONDS 0
#define RTC_VALL_HOURS 1
#define RTC_VALH_WEEKDAY 1

//define lock and unlock macros for RTCC
#define  RTCCUnLock() do {EECON2 = 0x55; EECON2 = 0xAA; RTCCFGbits.RTCWREN = 1;} while (0)
#define  RTCCLock()   RTCCFGbits.RTCWREN=0

void clock_handle_alarms();

void clock_set_second_digit(uint8_t digit, uint8_t second);
void clock_set_minute_digit(uint8_t digit, uint8_t minute);
void clock_set_hour_digit(uint8_t digit, uint8_t hour);
uint8_t clock_get_minute_digit(uint8_t digitnum);
uint8_t clock_get_minute();
uint8_t clock_get_hour_digit(uint8_t digitnum);
uint8_t clock_get_hour();
uint8_t clock_get_second_digit(uint8_t digitnum);

void clock_set_alarm_second_digit(uint8_t digit, uint8_t second);
void clock_set_alarm_minute_digit(uint8_t digit, uint8_t minute);
void clock_set_alarm_hour_digit(uint8_t digit, uint8_t hour);
uint8_t clock_get_alarm_minute_digit(uint8_t digitnum);
uint8_t clock_get_alarm_minute();
uint8_t clock_get_alarm_hour_digit(uint8_t digitnum);
uint8_t clock_get_alarm_hour();
uint8_t clock_get_alarm_second_digit(uint8_t digitnum);

void clock_disable_alarm();
void clock_enable_alarm();

void clock_increase_time(int increment_amount);
void clock_increase_alarm_time(int increment_amount);

void clock_snooze_alarm();
void clock_snooze_stop();

#ifdef	__cplusplus

#endif

#endif	/* CLOCK_H */

