/*
 * File:   Lab7_1.c
 * Author: wgkot
 *
 * Created on September 14, 2022, 4:04 PM
 */

// CONFIG2
#pragma config POSCMOD = HS             // Primary Oscillator Select (HS Oscillator mode selected)
#pragma config I2C1SEL = PRI            // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = ON             // IOLOCK Protection (Once IOLOCK is set, cannot be changed)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRCDIV           // Oscillator Select (Fast RC Oscillator with Postscaler (FRCDIV))
#pragma config SOSCSEL = SOSC           // Sec Oscillator Select (Default Secondary Oscillator (SOSC))
#pragma config WUTSEL = LEG             // Wake-up timer Select (Legacy Wake-up Timer)
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF              // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx1               // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = ON              // JTAG Port Enable (JTAG port is enabled)

#include "p24FJ64GA002.h"
#include <stdio.h>
#include <stdlib.h>
#include "xc.h"

// Header file includes
#include "p24FJ64GA002.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "pin_functions.h"



// Define instruction clock frequency
#ifndef FCY
 // Unless already defined assume 4MHz instruction clock frequency
 // This definition is required to calibrate __delay_us() and __delay_ms()
   #define FCY 4000000UL
#endif 

int main(void) {
    
    // Set-up & configure mapping for pins as output
    setupPins();
    // Initialise display
    Lcd8_Init();
    // Clear LCD
    Lcd8_Clear();
    while (1)
    {
       Lcd8_Write_String("B D F H J L N P R T V X Z") ; 
        
    }
    return 0;
}
