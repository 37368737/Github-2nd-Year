/* 
 * File:   functions.h
 * Author: Herman Blackie & Melvin Ferreira
 * Contribution acknowledgment to electroSome
 * Created on 15 September 2016, 10:11 AM
 */

#ifndef LCD_H
#define LCD_H

#ifndef FCY
 // Unless already defined assume 4MHz instruction clock frequency
 // This definition is required to calibrate __delay_us() and __delay_ms()
 #define FCY 4000000UL
#endif  

// This is to ensure that pin mappings are pulled through to functions
#include "pin_functions.h"
// Include for delay functions, NOTE: minimum time that can be requested is 12X instruction periods! See libpic30.h
#include    <libpic30.h>

//Function prototypes
void Lcd8_Port(char a) ;
void Lcd8_Cmd(char a) ;
void Lcd8_Cmd(char a) ;
void Lcd8_Clear() ;
void Lcd8_Home() ;
void Lcd8_Set_Cursor(char a, char b) ;
void Lcd8_Init() ;
void Lcd8_Write_Char(char a) ;
void Lcd8_Write_String(char *a) ;
void Lcd8_Shift_Right() ;
void Lcd8_Shift_Left() ;

#endif // LCD_H