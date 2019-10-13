#include <xc.h>
#include "uart.h"

void uartsetup(char which, long clock, long baud) {
    if (which == 0) {
        TRISBbits.TRISB15 = 1;
        ANSELBbits.ANSB15 = 0;

        TRISBbits.TRISB14 = 0;
        ANSELBbits.ANSB14 = 0;

        U1MODEbits.SLPEN = 1;
        U1MODEbits.CLKSEL = 1;
        U1MODEbits.OVFDIS = 1;
        U1MODEbits.SIDL = 0;
        U1MODEbits.IREN = 0;
        U1MODEbits.WAKE = 0;
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
        U1STAbits.URXISEL = 1;
        U1STAbits.ADDEN = 0;

        U1BRG = clock / baud;

        U1MODEbits.ACTIVE = 1;
        U1MODEbits.ON = 1;
    }else if(which == 1){
        TRISAbits.TRISA4 = 1;
        RPINR9bits.U2RXR = 5;
        
        TRISBbits.TRISB5 = 0;
        RPOR2bits.RP11R = 4;

        U2MODEbits.SLPEN = 1;
        U2MODEbits.CLKSEL = 1;
        U2MODEbits.OVFDIS = 1;
        U2MODEbits.SIDL = 0;
        U2MODEbits.IREN = 0;
        U2MODEbits.WAKE = 0;
        U2MODEbits.LPBACK = 0;
        U2MODEbits.ABAUD = 0;
        U2MODEbits.RXINV = 0;
        U2MODEbits.BRGH = 1;
        U2MODEbits.PDSEL = 0;
        U2MODEbits.STSEL = 0;

        U2MODEbits.RTSMD = 1; //?
        U2MODEbits.UEN = 0; // ?

        U2STAbits.MASK = 0;
        U2STAbits.ADDR = 0;
        U2STAbits.UTXISEL = 2;
        U2STAbits.UTXINV = 0;
        U2STAbits.URXEN = 1;
        U2STAbits.UTXBRK = 0;
        U2STAbits.UTXEN = 1;
        U2STAbits.URXISEL = 1;
        U2STAbits.ADDEN = 0;

        U2BRG = clock / baud;

        U2MODEbits.ACTIVE = 1;
        U2MODEbits.ON = 1;
    }
}

void uart_rx_interrupt(char which, char state) {
    if (which == 0) {
        //Int priorities
        IPC13bits.U1RXIP = 5;
        IPC13bits.U1RXIS = 1;
        //Int flags
        IFS1bits.U1RXIF = 0;
        //Int enable/disable
        IEC1bits.U1EIE = 0;
        IEC1bits.U1TXIE = 0;
        IEC1bits.U1RXIE = state; //Enable int on RX
    }else if(which == 1){
        //Int priorities
        IPC14bits.U2RXIP = 6;
        IPC14bits.U2RXIS = 1;
        //Int flags
        IFS1bits.U2RXIF = 0;
        //Int enable/disable
        IEC1bits.U2EIE = 0;
        IEC1bits.U2TXIE = 0;
        IEC1bits.U2RXIE = state; //Enable int on RX
    }
}

void uartsend(char fromwhere, char val) {
    if (fromwhere == 0) {
        while (IFS1bits.U1TXIF == 0); // hold the program till TX buffer is free
        U1TXREG = val; //Load the transmitter buffer with the received value
        while (IFS1bits.U1TXIF == 0); // hold the program till TX buffer is free
    }else if(fromwhere == 1){
        while (IFS1bits.U2TXIF == 0); // hold the program till TX buffer is free
        U2TXREG = val; //Load the transmitter buffer with the received value
        while (IFS1bits.U2TXIF == 0); // hold the program till TX buffer is free
    }
}

char uartread(char fromwhere) {
    char val;
    if (fromwhere == 0) {
        val = U1RXREG;
        IFS1CLR = _IFS1_U1RXIF_MASK;
        return val;
    }else if(fromwhere == 1){
        val = U2RXREG;
        IFS1CLR = _IFS1_U2RXIF_MASK;
        return val;
    }
}
