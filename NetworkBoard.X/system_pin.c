#include "system_pin.h"
#include <xc.h>

void setup_io() {
    OSCCON = 0x00000000;
    SPLLCONbits.PLLODIV = 0;
    SPLLCONbits.PLLMULT = 6;
    SPLLCONbits.PLLICLK = 1;
    
    //Address Pins
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSA0 = 1;
    TRISAbits.TRISA1 = 1;
    ANSELAbits.ANSA1 = 1;   
    
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;
    TRISCbits.TRISC9 = 0;
    
    TRISBbits.TRISB10 = 1;
    TRISBbits.TRISB11 = 1;
}