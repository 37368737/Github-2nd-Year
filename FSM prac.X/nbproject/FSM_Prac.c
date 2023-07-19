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
#include <stdint.h>
#include "pin_functions.h"
#include "lcd.h"

// Define instruction clock frequency
#ifndef FCY
 // Unless already defined assume 4MHz instruction clock frequency
 // This definition is required to calibrate __delay_us() and __delay_ms()
   #define FCY 4000000UL
#endif 

char str[16] ;
int statenum[10] = {0,1,2,3,4,5,6,7,8,9};
int num = 1;
int i = 1;
int j = 0;
    
int main(void) {
        
    RPINR0bits.INT1R = 9;              //Set pin RB8 as input for peripheral interrupt 1
    
    RPOR4bits.RP8R = 20;               //Set RB9 as output
    OC3CONbits.OCSIDL=0;
    OC3CONbits.OCFLT=0;
    OC3CONbits.OCTSEL=0;
    OC3CONbits.OCM=110;
    PR2 = 8000-1;
    OC3RS = 2000;
    OC3R = 2000;
    T2CON = 0x8000;
    
    // Set-up & configure mapping for pins as output
    setupPins();
    // Initialise display
    Lcd8_Init();
    // Clear LCD
    Lcd8_Clear();
    
    
    while (1)
    {
       sprintf(str,"%d",num) ;
       Lcd8_Set_Cursor(2,0);
       Lcd8_Write_String(str) ;
       __delay_ms(500)
       Lcd8_Set_Cursor(1,0);     
       Lcd8_Write_String("BDFHJLNPRTVXZ") ;
       
       
        
    }
    
    //initialisations of  external interrupt 1 here
    
    INTCON1bits.NSTDIS = 1;            //Nested interrupts disabled.
    INTCON2bits.INT1EP = 0;            //negative edge trigger.
    IFS1bits.INT1IF = 0;               //Interrupt flag - request has not occurred.
    IEC1bits.INT1IE = 1;               //Interrupt request is enabled.
    
    LATBbits.LATB15 = 0;
    LATAbits.LATA1 = 0;
    
    //set as output
    TRISBbits.TRISB15 = 0;    
    TRISAbits.TRISA1 = 0;
    //LATBbits.LATB15 = 1 ;
    
    PR5 = 40625-1;
    T5CON = 0x8020;
    TMR5 = 0;
    OC1CONbits.OCM=110;
    
    //setup interrupt2
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
    
    TRISAbits.TRISA1 = 1;
    
    return 0;
}


void _ISR _INT1Interrupt(void)  // 1'st interrupt
{
  i = i+1;
    if (i>10)
    {
        i=0;
        ;
    }
  switch(statenum[i])
    {
        case 1:
           
            
                num = 1;
                sprintf(str,"%d",num) ;
  Lcd8_Set_Cursor(2,0);
  Lcd8_Write_String(str) ;
                
            
            break;
        case 2:
            
            num =2;
                sprintf(str,"%d",num) ;
  Lcd8_Set_Cursor(2,0);
  Lcd8_Write_String(str) ;
            
            break;
        case 3:
            
            num = 3;
                sprintf(str,"%d",num) ;
  Lcd8_Set_Cursor(2,0);
  Lcd8_Write_String(str) ;
                
            
            break;
        case 4:
            
            num = 4;
                sprintf(str,"%d",num) ;
  Lcd8_Set_Cursor(2,0);
  Lcd8_Write_String(str) ;
            
            break;
        case 5:
            
            num = 5;
                sprintf(str,"%d",num) ;
  Lcd8_Set_Cursor(2,0);
  Lcd8_Write_String(str) ;
                
            
            break;
        case 6:
            
            num = 6;
                sprintf(str,"%d",num) ;
  Lcd8_Set_Cursor(2,0);
  Lcd8_Write_String(str) ;
                
            
            break;
        case 7:
            
            num = 7;
              sprintf(str,"%d",num) ;
  Lcd8_Set_Cursor(2,0);
  Lcd8_Write_String(str) ;  
                
            
            break;
        case 8:
            
            num = 8;
               sprintf(str,"%d",num) ;
  Lcd8_Set_Cursor(2,0);
  Lcd8_Write_String(str) ; 
                
            
            break;
        case 9:
            
            num = 9;
               sprintf(str,"%d",num) ;
  Lcd8_Set_Cursor(2,0);
  Lcd8_Write_String(str) ; 
                
            
            break;
        case 10:
            
            num = 10;
                sprintf(str,"%d",num) ;
  Lcd8_Set_Cursor(2,0);
  Lcd8_Write_String(str) ;
                
            
            break;
      default:
          
          num = 1;
          
          break;
  }
  
  
  IFS1bits.INT1IF = 0;
}
void _ISR _T5Interrupt(void)
{
    if (j<4){
         LATAbits.LATA1 = 0 ;
         IFS0bits.T2IF = 0;
         j++;
    }
    else if (j=4){
        LATAbits.LATA1 = 0 ;
        IFS0bits.T2IF = 0;
        j=0;
    }
    
    return;
}
