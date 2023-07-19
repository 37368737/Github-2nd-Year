/* 
 * File:   pin_functions.h
 * Author: Herman Blackie
 *
 * Created on 15 September 2016, 10:11 AM
 * Modified on 20 August 2017 - Pin definitions changed - M. Ferreira
 */

#ifndef PIN_FUNCTIONS_H
#define	PIN_FUNCTIONS_H

#include "p24FJ64GA002.h"

// Define all the pins. needed to control the LCD commands and data pins

#define RS LATBbits.LATB2
#define EN LATBbits.LATB3
#define D0 LATBbits.LATB4
#define D1 LATAbits.LATA4
#define D2 LATBbits.LATB5
#define D3 LATBbits.LATB6
#define D4 LATBbits.LATB7
#define D5 LATBbits.LATB12
#define D6 LATBbits.LATB13
#define D7 LATBbits.LATB14

// Function prototypes
// Function enables pins required I/O pins as output
void setupPins() ;

#endif	/* FUNCTIONS_H */


