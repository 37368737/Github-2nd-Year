//******************************************************************************
//  PROGRAM:       Lab8_2022.c
//  DESCRIPTION:   LAB 8 skeleton code

//------------------------------------------------------------------------------
//  HEADER FILES
//------------------------------------------------------------------------------
#include "p24FJ64GA002.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pin_functions.h"
#include "lcd.h"
//------------------------------------------------------------------------------
//  GLOBAL VARIABLE DECLARATIONS
//------------------------------------------------------------------------------
volatile unsigned int ADC_average;  // holds ADC average 
//------------------------------------------------------------------------------
//  FUNCTION PROTOTYPES
//------------------------------------------------------------------------------
unsigned int ADC10Avg(void) ;
double ADCconvert_value(unsigned int x) ;

int main(void)
{
    
    char str[16] ;  // Buffer to store text strings for LCD
    
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
    Lcd8_Write_String("REII 222 2022");
    Lcd8_Set_Cursor(2,2);
    Lcd8_Write_String("LAB 8: ADC");
      __delay_ms(2000) ;
    Lcd8_Clear();
    Lcd8_Set_Cursor(1,0);
    Lcd8_Write_String("OUTPUT CODE:") ;
    Lcd8_Set_Cursor(2,0);
    Lcd8_Write_String("VOLTAGE:") ;
   
    // Initialise status LED as A/D process on pin RB15
    TRISBbits.TRISB15 = 0 ;
    // Set initial state
    LATBbits.LATB15 = 0 ;
  
   // AD1CON1 register setup 
   AD1CON1bits.ADON = 0 ;// A/D converter is off - first configure device.
   AD1CON1bits.ADSIDL = 0 ; // Continue A/D operation in IDLE mode (N.A currently)
   AD1CON1bits.FORM = 0b00 ; // Data output in integer format - NB for variable declaration!
   AD1CON1bits.SSRC = 0b111 ; // Conversion trigger source select (auto)) sample time determined by SAMC bits in AD1CON3
   AD1CON1bits.ASAM = 1 ; //Sample auto start bit set

   // AD1CON2 register setup
   AD1CON2bits.VCFG0 = 0; // Voltage reference configuration tied to Vdd & Vss.
   AD1CON2bits.VCFG1 = 0;
   AD1CON2bits.VCFG2 = 0;
    
   AD1CON2bits.CSCNA = 0 ; // Scan input selection disabled
    
   AD1CON2bits.BUFM = 0 ; // 16bit (1 word buffer selected)
   AD1CON2bits.ALTS = 0 ;
  
   AD1CON2bits.SMPI = 0b1111 ; // Interrupt at completion of conversion of 16th sample
    
   // AD1CON3 register setup
   AD1CON3bits.ADRC   = 0 ;   // Clock derived from system clock - no post-scaler on clock to A/D unit
   AD1CON3bits.SAMC = 0b11110;  // set auto-sample time to 30*TAD, i.e. 30us. Time to switch from sampling to conversion in A/D cycle. Min 12 TAD required so more than enough time
   AD1CON3bits.ADCS = 1;     // TAD = 1*TCY = 250ns. Thus it is set that 1 TAD = 1us  TAD min per the data sheet = 75ns
  
   //  Select channel to sample
   AD1CHSbits.CH0SA = 0b0000 ; // Select AN0 to convert. ANO connected to trimpot.
   //  Start sample period
   //  Stop sample period & start conversion
   //  Retrieve result from buffer*
   //  Select next ADC channels
   //  Retrieve result from buffer*
    
   // Setup AD1 ISR, From datasheet, table 7.2, applicable registers: IFS0<13> IEC0<13> IPC3<4:6>
    // (This example assigns level 1 priority)
    IPC3bits.AD1IP = 0b001; 
    //Clear the Timer1 interrupt status flag
    IFS0bits.AD1IF = 0 ; 
    // Enable interrupts for AD1
    IEC0bits.AD1IE = 1 ;
     
    AD1CON1bits.ADON = 1 ;// A/D converter is configured - switch A/D on
    
    // Initial values for FSM here
    
    while(1)
    {
        
        // Display ADC value read on LCD
        sprintf(str,"%4i",ADC_average) ;
        Lcd8_Set_Cursor(1,9);
        Lcd8_Write_String(str) ;
    
        // Code to display voltage 
        //Use function "double ADCconvert_value(unsigned int x)" to do conversion   
        sprintf(str,"%1.3f V",ADCconvert_value(ADC_average)) ;
        Lcd8_Set_Cursor(2,9);
        Lcd8_Write_String(str) ;
        
    }
}

// Setup AD1 ISR. From datasheet, table 7.2, applicable registers: IFS0<13> IEC0<13> IPC3<4:6>
void __attribute__((interrupt, auto_psv)) _ADC1Interrupt(void)
{   /* Interrupt Service Routine code goes here */
       // Status LED to check that ISR is up and running
       LATBbits.LATB15 ^= 1 ;
       ADC_average = ADC10Avg(); // Take average of 16 samples - better practice to do this outside ISR but for example code and clarity we do it here
       //Reset AD1 interrupt flag and Return from ISR
       IFS0bits.AD1IF = 0;
}

//==============================================================================
//  FUNCTION:     ADCAvg10()
//  DESCRIPTION:  Average 16 ADC samples 10 bit
//  PARAMETERS:   none
//  RETURNS:      ADC_average
//  REQUIREMENTS: none
//==============================================================================
unsigned int ADC10Avg(void)
{
    unsigned long int x;
    // ADC values in ADC1BUFx, see table 4-16
    x = ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + // add all 16 samples
           ADC1BUF4 + ADC1BUF5 + ADC1BUF6 + ADC1BUF7 +
           ADC1BUF8 + ADC1BUF9 + ADC1BUFA + ADC1BUFB +
           ADC1BUFC + ADC1BUFD + ADC1BUFE + ADC1BUFF;
    x /= 16;            // shortcut for "x = x/16;"     
    return (unsigned int)x;  // cast x as unsigned char, it will never be more                            
}

//==============================================================================
//  FUNCTION:     ADCconvert_value()
//  DESCRIPTION:  Convert 10 bit ADC value to voltage
//  PARAMETERS:   x - Quantised 10-bit value (Range 0 -1023)
//  RETURNS:      y - voltage value represented by x
//  REQUIREMENTS: none
//==============================================================================
double ADCconvert_value(unsigned int x)
{
    double y = 0 ;
    y=(x+0.5)*(3.29)/1024;
    return (double)y ;
}
