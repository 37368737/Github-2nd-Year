/*
 * File:   pin_functions.c
 * Author: Herman Blackie & Melvin Ferreira
 * Created on 26 September 2016, 12:14 PM
 * Modified on 20 August 2017 - Pin definitions changed - TRIS registers updated - M. Ferreira
 */

#include "pin_functions.h"

// Function enables pins required I/O pins as output. Change as required
void setupPins(){
    /* 7 data pins D0-D7*/
    /* 2 Control pins - RS & EN */
    /*All the pins are set as outputs*/
     
    TRISBbits.TRISB2 = 0; // RS
    TRISBbits.TRISB3 = 0; // EN
    TRISBbits.TRISB4 = 0; //DB0
    TRISAbits.TRISA4 = 0; //DB1
    TRISBbits.TRISB5 = 0; //DB2
    TRISBbits.TRISB6 = 0; //DB3
    TRISBbits.TRISB7 = 0; //DB4
    TRISBbits.TRISB12 = 0; //DB5
    TRISBbits.TRISB13 = 0; //DB6
    TRISBbits.TRISB14 = 0; //DB7
    
    // Set initial values on all pins as low
    RS = 0 ;
    EN = 0 ; 
    D0 = 0 ;
    D1 = 0 ; 
    D2 = 0 ; 
    D3 = 0 ;
    D4 = 0 ;
    D5 = 0 ;
    D6 = 0 ;
    D7 = 0 ;
}
