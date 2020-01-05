#include "system_pin.h"
#include <xc.h>

void setup_io() {   
    // LED Setup
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB8 = 0;
    
    // Address Pins
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSA0 = 1;
    TRISAbits.TRISA1 = 1;
    ANSELAbits.ANSA1 = 1;   
    
    // System Outputs
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB11 = 0;
    
    // System Inputs
    TRISAbits.TRISA4 = 1;
    RPINR1bits.INT4R = 5;
    INTCONbits.INT4EP = 0;
    IEC0bits.INT4IE = 0;
    IFS0bits.INT4IF = 0; // Clear interrupt flag for timer 2
    IPC1bits.INT4IP = 3; // Interrupt priority 3
    IEC0bits.INT4IE = 1; // Enable Timer 2 Interrupt
    
    TRISBbits.TRISB10 = 1;
}