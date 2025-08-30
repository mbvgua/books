/*
 * Digital Clock.c
 *
 * Created: 30/11/2021 11:01:32
 * Author : son Kipkorir
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "LCD4.h"
#include "Keypad2.h"
#include "RTC.h"
#include "12C.h"
#define  TimeFormat12		0x40	/* Define 12 hour format */

int *set_time(void);
int convert_to_BCD(int  Number);


unsigned char keycheck;
int c;

void inter_Init(void){
	DDRD |= (0<<PD2); /* PORTD as input */
	PORTD |= (1<<PD2); /* Activate pull up resistor high */
	
	GICR = 1<<INT0;  /* Enable INT0*/
	MCUCR = (1<<ISC01) | (1<<ISC00); /* Trigger INT0 on rising edge */
	sei();
}


ISR(INT0_vect){
char value = (PINB & (0x0F));
keycheck = check_Keypad(value);
c=1;

}	






int main(void)
{
    char buffer[20];
    //char* days[7]= {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

    I2C_Init();			/* Initialize I2C */
    LCD_Init();		/* Initialize LCD16x2 */
	inter_Init();
    display_Custom_Char();
	LCD_String("   NOT SET.");
	_delay_ms(10);
 
    while (1) 
    {
          
		
		if((keycheck=='=') && (c==1)){
			int *p;
            p=set_time();
			LCD_String("nikupendeeee");
			_delay_ms(1000);
			LCD_Clear();
            RTC_Clock_Write( p, (p+1), (p+2), 0 );
			c=0;
			 display_Custom_Char();
			 LCD_String("   NOT SET.");
			
		}
		if((keycheck=='+') && (c==1)){
			
			LCD_Clear();
			LCD_String("SET ALARM");
			_delay_ms(1000);
			LCD_Clear();
			c=0;
			 display_Custom_Char();
			 LCD_String("   NOT SET.");
		}
		
		if((keycheck=='C')&&(c==1)){
			LCD_Clear();
			LCD_String("ALARM ACTIVE");
			_delay_ms(1000);
			LCD_Clear();
			c=0;
			 display_Custom_Char();
			 LCD_String("   NOT SET.");
		}
		
		
		RTC_Read_Clock(0);	/* Read clock with second add. i.e location is 0 */
		
		if (hour & TimeFormat12)
		{
			sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
			if(IsItPM(hour))
			strcat(buffer, "PM");
			else
			strcat(buffer, "AM");
			LCD_String_xy(0,0,buffer);
		}
		
		else
		{
			sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
			LCD_String_xy(0,0,buffer);
		}
		
		
		
    }
	return 0;
}

int convert_to_BCD(int  Number){
	int b = ((Number/10)*16)+(Number%10);
	return b;
}


int *set_time(void){
	LCD_Clear();
	LCD_String("SET TIME");
	_delay_ms(1000);
	LCD_Clear();
	c=0;
	//should not read initial value of keycheck which will be '='
	//take first key check value
	char *first_value[0], *second_value[0], *hour_value[0], buffer[0];
	int first_number, Second_number, hour_number, BCD_hour_value;
    int New_hour, New_minute, New_second;
    int love[2];
	int order=0;

for(int t=0; t<3; t++)
{

	 
	 int d=0;
     keycheck = '=';
	while (keycheck!='/' )
	{
	   while (d==0)
	   {
        LCD_Clear();
        LCD_String("In while loop.");
        _delay_ms(1000);
        LCD_Clear();
        order =0;
        d++;
		}

     if ((keycheck!='=')&&(c==1)&&(order==0))
	                   {
		                      //first value
		                      first_value[0] = keycheck; 
		                      first_number = atoi(first_value);
		                      itoa(first_number, buffer, 10);
							  LCD_String(buffer);
		                      order =1;
		                      c=0;
	                    }
	
	         if ((order==1)&&(c==1))
	                     {
		                      first_number = first_number*10;
							  itoa(first_number, buffer, 10);
		                      second_value[0] = keycheck;
		                      LCD_String(buffer);
							  LCD_Cmd(0xC0);
							  
							  
		                      Second_number = atoi(second_value);
		                      hour_number = first_number + Second_number;
							  itoa(hour_number, buffer, 10);
							  /*LCD_String(buffer);
							  _delay_ms(10);*/
							  LCD_String("press / to enter");
		                      c=0;
		                      order=3;
	                      }
	}
	
	    LCD_Clear();
		itoa(hour_number, buffer, 10);
		LCD_String("value to be set");
		BCD_hour_value = convert_to_BCD(hour_number);
		itoa(BCD_hour_value, buffer, 10);
		LCD_Cmd(0xC0);
		LCD_String(buffer);
		_delay_ms(1000);
		LCD_Clear();
if (t==0)
{
 New_hour=BCD_hour_value;
LCD_String("t==0");
_delay_ms(1000);
LCD_Clear();
love[0]=New_hour;
continue;
}

if (t==1)
{
	New_minute=BCD_hour_value;
LCD_String("t==1");
_delay_ms(1000);
LCD_Clear();
love[1]=New_minute;
continue;
}

if (t==2)
{
	New_second=BCD_hour_value;
LCD_String("t==2");
_delay_ms(1000);
LCD_Clear();
love[2]=New_second;
continue;
}
	
	
}
	return love;
	// if there are two values multiply initial value by 10 then add the new key check vaue
	//pressing A means you are done entering and it should move to seconds
	// we begin with hours, then minutes then seconds
	
}