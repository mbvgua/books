/*
 * LCD4.h
 *
 * Created: 28/10/2021 11:47:31
 *  Author: son Kipkorir
 */ 


#ifndef LCD4_H_
#define LCD4_H_

void Load_Custom_Char(void);
void LCD_Cmd(unsigned char cmd);
void LCD_Char (unsigned char char_data);
void LCD_Init (void);
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear(void);
void display_Custom_Char(void);

#endif /* LCD4_H_ */