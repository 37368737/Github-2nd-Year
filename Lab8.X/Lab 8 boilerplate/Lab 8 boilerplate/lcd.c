/*
 * File:   lcd.c
 * Author: Herman Blackie & Melvin Ferreira
 * Contribution acknowledgment to electroSome
 * Contains all the functions defined as prototypes in lcd.h
 * Created on 26 September 2016, 12:00 PM
 * Modified on 25 August 2017 - Comments updated for latest data sheet &
 * recommended wait times amended to corresponding to LMB162abc-1 LCD unit with 
 * ST7066U LCD driver - M. Ferreira
 * Modified 30 September 2019 - delay for clear instructions extended to 1620us
 * It seems that driver & controller chip has changed to S6A0065 & S6A0069.
 * The implications of this has not been incorporated into the code
 * New timing diagrams not verified! - left as exercise to user...
 */

#include    "lcd.h"

//LCD 8 Bit Interfacing Functions

// Function writes input received from "a" in 8-bit format (D0-D7)
void Lcd8_Port(char a)
{
	// Determine value for D0 (Bitwise and of a & 0b00000001))
    if(a & 1)
		D0 = 1;
	else 
		D0 = 0;
    // Determine value for D1 (Bitwise and of a & 0b00000010))
	if(a & 2)
		D1 = 1;
	else
		D1 = 0;
    // Determine value for D2 (Bitwise and of a & 0b00000100))
	if(a & 4)
		D2 = 1;
	else
		D2 = 0;
	// Determine value for D3 (Bitwise and of a & 0b00001000))
	if(a & 8)
		D3 = 1;
	else
		D3 = 0;
	// Determine value for D4 (Bitwise and of a & 0b00010000))
	if(a & 16)
		D4 = 1;
	else
		D4 = 0;
    // Determine value for D5 (Bitwise and of a & 0b00100000))
	if(a & 32)
		D5 = 1;
	else
		D5 = 0;
	// Determine value for D6 (Bitwise and of a & 0b01000000))
	if(a & 64)
		D6 = 1;
	else 
		D6 = 0;
    // Determine value for D6 (Bitwise and of a & 0b10000000))
	if(a & 128)
		D7 = 1;
	else
		D7 = 0;
}

// This function is called to transfer instruction data to the LCD
// Function is written, assuming R/W is already low
void Lcd8_Cmd(char a)
{     
  RS = 0;             // => RS = 0, transfer instruction data  
  Lcd8_Port(a);       // Instruction transfer
  // Address set-up time 5ns min
  __delay_us(100) ;
  EN  = 1;             // => Data Enable = 1 on LCD
  // Data set-up time (100ns) and Enable Pulse width (575ns))
  __delay_us(200) ;
  EN  = 0;             // => E = 0
  // Data & Address hold time (13ns) and Enable cycle time total (1500ns)
  __delay_us(100) ;
}

// Command to clear display
void Lcd8_Clear()
{
    // See command number 1, section 4.4, LMB162abc-1 datasheet
    Lcd8_Cmd(0x01);
    // Observe delay after clear, ST7066U datasheet, page 17, min 1.52ms
    __delay_us(1620) ;
}

// Function to return cursor home
void Lcd8_Home()
{
    // See command number 2, section 4.4, datasheet
    Lcd8_Cmd(0x02) ;
    // Observe delay after clear, ST7066U datasheet, page 17, min 1.52ms
    __delay_us(1620) ;
}


// Function sets location of cursor, argument a is for line, argument b is for address (O-15))
// See command 8, section 4.5
void Lcd8_Set_Cursor(char a, char b)
{
	if(a == 1)
	  Lcd8_Cmd(0x80 + b);
	else if(a == 2)
	  Lcd8_Cmd(0xC0 + b);
}


// Initialise LCD display
void Lcd8_Init()
{
    // Give LCD time to start-up after reset, min. 50ms according to section 4.2, datasheet
    __delay_ms(100) ;
    
    // Default values are now as follows
    // To change see command 6, section 4., datasheet
    // 0b001100xx = 0x30
    //DL = 1 8-bit interface
    //N=0 1-line display
    //F=0 5x8 character font
    //D=0 Display off
    //C=0 Cursor off
    //B=0 Blink off
    //I/D=1 Increment by 1
    //S=0 No shift

    // To understand workings of these commands - refer to command set in datasheet, section 4.4
    // Function set, command
    Lcd8_Cmd(0b00111000) ; // 2-line display, 8-bit interface 5x8 dots font, see description above
    // Display on/off command
    Lcd8_Cmd(0b00001111) ; // Display on, cursor on, blink on, See command 4, section 4.4
    Lcd8_Clear(); // Clear display
    // Set Entry mode command
    Lcd8_Cmd(0b00000110) ;// I/D= 1, increment cursor position, S=0, no screen shift Entry mode set, see command 3, section 4.5  
    // Initialise Set data Enable low
}

// This function is called to transfer display data to the LCD
// Function is written, assuming R/W is already low, see command 10, section 4.4
void Lcd8_Write_Char(char a)
{
   RS = 1 ;             // => RS = 1, transfer display data, section  1.4
   Lcd8_Port(a);       // Data transfer 
   // Address set-up time 50ns min - accounted for by calling Lcd8_Port
   __delay_us(100) ;
   EN  = 1;             // => Data Enable = 1 on LCD
   // Data set-up time (100ns) and Enable Pulse width (575ns))
   __delay_us(200) ;
   EN  = 0;             // => E = 0
   // Data & Address hold time (13ns) and Enable cycle time total (1500ns)
   __delay_us(100) ;
}

// Function writes string to LCD display
void Lcd8_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
        Lcd8_Write_Char(a[i]);
}

void Lcd8_Shift_Right()
{
	Lcd8_Cmd(0x1C);
}

void Lcd8_Shift_Left()
{
	Lcd8_Cmd(0x18);
}


