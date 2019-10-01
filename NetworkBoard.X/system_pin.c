#include "system_pin.h"
#include <xc.h>

void setup_io() {
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB13 = 0;
    ANSELBbits.ANSB13 = 0;
    
    TRISBbits.TRISB10 = 1;
    TRISBbits.TRISB11 = 1;
    
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSA0 = 1;
    TRISAbits.TRISA1 = 1;
    ANSELAbits.ANSA1 = 1;   
}