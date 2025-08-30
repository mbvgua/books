/*
 * _12C.h
 *
 * Created: 02/12/2021 09:42:26
 *  Author: son Kipkorir
 */ 


#ifndef T2C_H_
#define T2C_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <math.h>
#define SCL_CLK 100000UL
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))


uint8_t I2C_Start(char write_address) ;
uint8_t I2C_Repeated_Start(char read_address) ;
void I2C_Stop(void);
void I2C_Start_Wait(char write_address);
uint8_t I2C_Write(char data);
char I2C_Read_Ack(void);
char I2C_Read_Nack(void);
void I2C_Slave_Init(uint8_t slave_address);
int8_t I2C_Slave_Listen(void);
int8_t I2C_Slave_Transmit(char data);
char I2C_Slave_Receive(void);




#endif /* 12C_H_ */