#include <xc.h>
#include "uart.h"

void uartsetup(char which, long clock, int baud){
    if(which == 0){
        IPC13bits.U1RXIP = 1;
        IEC1bits.U1RXIE = 1;
        
        TRISBbits.TRISB15 = 1;
        ANSELBbits.ANSB15 = 0;
        
        TRISBbits.TRISB14 = 0;
        ANSELBbits.ANSB14 = 0;

        U1MODEbits.SLPEN = 1;
        U1MODEbits.CLKSEL = 1;
        U1MODEbits.OVFDIS = 1;
        U1MODEbits.SIDL = 0;
        U1MODEbits.IREN = 0;
        U1MODEbits.WAKE = 1;
        U1MODEbits.LPBACK = 0;
        U1MODEbits.ABAUD = 0;
        U1MODEbits.RXINV = 0;
        U1MODEbits.BRGH = 1;
        U1MODEbits.PDSEL = 0;
        U1MODEbits.STSEL = 0;
        
        U1MODEbits.RTSMD = 1; //?
        U1MODEbits.UEN = 0; // ?
        
        U1STAbits.MASK = 0;
        U1STAbits.ADDR = 0;
        U1STAbits.UTXISEL = 2;
        U1STAbits.UTXINV = 0;
        U1STAbits.URXEN = 1;
        U1STAbits.UTXBRK = 0;
        U1STAbits.UTXEN = 1;
        U1STAbits.URXISEL = 0;
        U1STAbits.ADDEN = 0;
        
        U1BRG = clock/baud;
        
        U1MODEbits.ACTIVE = 1;
        U1MODEbits.ON = 1;
    }
}

void uartsend(char fromwhere, char val){
    if(fromwhere == 0){
        while(IFS1bits.U1TXIF == 0); // hold the program till TX buffer is free
        U1TXREG = val; //Load the transmitter buffer with the received value
        while(IFS1bits.U1TXIF == 0); // hold the program till TX buffer is free
    }    
}

char uartread(char fromwhere){
    if(fromwhere == 0){
        return U1RXREG;
    }
}