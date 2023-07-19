/* 
 * File:   newmainXC16.c
 * Author: Herman Blackie & Melvin Ferreira
 *
 * Created on 14 September 2016, 2:03 PM
 * Modified on 20 August 2017 - Welcome message changed - M. Ferreira
 * Modified on 27 August 2018 - Added comments, welcome message changed
 * Modified on 30 September 2019 - Welcome message changed
 * Modified on 20 October 2020 - Welcome message changed, changed pragmas and 
 * header file includes to work with SNAP!
 * Modified on 13 October 2021 - Welcome message amended
 * Modified on 5 September 2022 - Welcome message amended


 */

// #pragma config statements should precede project file includes.
// Don't forget your pragma statements for configuration bits here
// CONFIG2
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary oscillator disabled)
#pragma config I2C1SEL = PRI            // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF            // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRC              // Oscillator Select (Fast RC Oscillator (FRC))
#pragma config SOSCSEL = SOSC           // Sec Oscillator Select (Default Secondary Oscillator (SOSC))
#pragma config WUTSEL = LEG             // Wake-up timer Select (Legacy Wake-up Timer)
#pragma config IESO = OFF               // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) disabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx1               // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)


// Header file includes
#include "p24FJ64GA002.h"
#include <stdio.h>
#include <stdlib.h>
#include "pin_functions.h"
#include "lcd.h"

// Define instruction clock frequency
#ifndef FCY
 // Unless already defined assume 4MHz instruction clock frequency
 // This definition is required to calibrate __delay_us() and __delay_ms()
   #define FCY 4000000UL
#endif 
int i = 0;

int main(void) 
{   
    LATAbits.LATA1 = 0;
    TRISAbits.TRISA1 = 0;
    
    //setup interrupt1
    IPC0bits.T1IP = 4;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    
    // setup timer 1
    PR1 = 31250 - 1;
    TMR1 = 0;
    // switch on with prescaler at 1:64, Fcy = 4 MHz, 500ms on, 500ms off.
    T1CON = 0x8020;
    
    LATAbits.LATA1 = 1;
    
    
    RPOR7bits.RP15R =18;
    OC1CONbits.OCSIDL=0;
    OC1CONbits.OCFLT=0;
    OC1CONbits.OCTSEL=0;
    PR2 = 19999;
    OC1RS = 0;
    OC1R = OC1RS ;
    T2CON = 0x8000;
    OC1CONbits.OCM=110;
    //initialisations here
    
    // LCD setup-up
    // Set-up & configure mapping for pins as output
    setupPins();
    // Initialise display
    Lcd8_Init();
    // Clear LCD
    Lcd8_Clear();
    Lcd8_Set_Cursor(1,0);
    Lcd8_Write_Char('1') ;
    Lcd8_Write_Char(':') ;
    Lcd8_Set_Cursor(2,0);
    Lcd8_Write_Char('2') ;
    Lcd8_Write_Char(':') ;
    Lcd8_Set_Cursor(1,2);
    Lcd8_Write_String(" WG KOTZEE");
    Lcd8_Set_Cursor(2,2);
    Lcd8_Write_String(" 37368737");
    
    while (1)
    {
        if (i == 1){
            OC1RS--;
            OC1R = OC1RS;
        }
        if (i == 0){
            OC1RS++;
            OC1R = OC1RS ;
        }    
        __delay_us(100);
        if (OC1RS >= 19999){
            i = 1;
        }
        if (OC1RS == 0){
            i = 0;
        }
        
        
        // Main program code here
    }
    
    return 0;
}
void _ISR _T1Interrupt(void)
{
    
    //flick LED RB 15
    LATAbits.LATA1 ^= 1;
    // clear flag 
    IFS0bits.T1IF = 0;
    
    return;
} 