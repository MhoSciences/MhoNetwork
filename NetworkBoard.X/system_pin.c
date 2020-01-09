#include "system_pin.h"
#include <xc.h>

void setDO(char pin, char value){
    switch (pin){
        case 0:
            EX0_setup   =   0;
            EX0_da      =   0;
            EX0_ops     =   0;
            EX0_o = value;
            break;
        case 1:
            EX1_setup   =   0;
            EX1_da      =   0;
            EX1_ops     =   0;
            EX1_o = value;
            break;
        case 2:
            EX2_setup   =   0;
            EX2_da      =   0;
            EX2_ops     =   0;
            EX2_o = value;
            break;
        case 3:
            EX3_setup   =   0;
            EX3_da      =   0;
            EX3_ops     =   0;
            EX3_o = value;
            break;
        case 4:
            EX4_setup   =   0;
            EX4_da      =   0;
            EX4_ops     =   0;
            EX4_o = value;
            break;
        case 5:
            EX5_setup   =   0;
            EX5_da      =   0;
            EX5_ops     =   0;
            EX5_o = value;
            break;
    }
}

char readDI(char pin){
    char value;
    switch (pin){
        case 0:
            EX0_setup   =   1;
            EX0_da      =   0;
            EX0_ops     =   0;
            value = EX0_i;
            break;
        case 1:
            EX1_setup   =   1;
            EX1_da      =   0;
            EX1_ops     =   0;
            value = EX1_i;
            break;
        case 2:
            EX2_setup   =   1;
            EX2_da      =   0;
            EX2_ops     =   0;
            value = EX2_i;
            break;
        case 3:
            EX3_setup   =   1;
            EX3_da      =   0;
            EX3_ops     =   0;
            value = EX3_i;
            break;
        case 4:
            EX4_setup   =   1;
            EX4_da      =   0;
            EX4_ops     =   0;
            value = EX4_i;
            break;
        case 5:
            EX5_setup   =   1;
            EX5_da      =   0;
            EX5_ops     =   0;
            value = EX5_i;
            break;
    }
}

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