/*
 * RTC.h
 *
 * Created: 03/12/2021 07:46:46
 *  Author: son Kipkorir
 */ 


#ifndef RTC_H_
#define RTC_H_

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void RTC_Clock_Write(char _hour, char _minute, char _second, char AMPM);
void RTC_Calendar_Write(char _day, char _date, char _month, char _year);
bool IsItPM(char hour_);
void RTC_Read_Clock(char read_clock_address);
void RTC_Read_Calendar(char read_calendar_address);
void RTC_Stop_Clock(void);

int second,minute,hour,day,date,month,year;



#endif /* RTC_H_ */