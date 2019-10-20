#include "ucontroller_config.h"
#include "delimiter_definitions.h"
#include "system_pin.h"
#include <xc.h>
#include <sys/attribs.h>
#include "adc.h"

#define SYS_FREQ 6000000

char array[256];
char d_index = 0;

void initDataTimer(int frequency)
{
    T2CON   = 0x0;      // Disable timer 2 when setting it up
    TMR2    = 0;        // Set timer 2 counter to 0
    IEC0bits.T2IE = 0;  // Disable Timer 2 Interrupt

    // Set up the period. Period = PBCLK3 frequency, which is SYS_FREQ / 2, divided by the frequency we want and then divided by 8 for our chosen pre-scaler.
    PR2 = SYS_FREQ / frequency;

    // Set up the pre-scaler
    T2CONbits.TCKPS = 0b110; // Pre-scale of 8

    IFS0bits.T2IF = 0;  // Clear interrupt flag for timer 2
    IPC4bits.T2IP = 3;  // Interrupt priority 3
    IEC0bits.T2IE = 1;  // Enable Timer 2 Interrupt

    // Turn on timer 2
    T2CONbits.TON   = 1;
}

void initConfigTimer(int frequency)
{
    T3CON   = 0x0;      // Disable timer 2 when setting it up
    TMR3    = 0;        // Set timer 2 counter to 0
    IEC0bits.T3IE = 0;  // Disable Timer 2 Interrupt

    // Set up the period. Period = PBCLK3 frequency, which is SYS_FREQ / 2, divided by the frequency we want and then divided by 8 for our chosen pre-scaler.
    PR3 = SYS_FREQ / frequency;

    // Set up the pre-scaler
    T3CONbits.TCKPS = 0b111; // Pre-scale of 8

    IFS0bits.T3IF = 0;  // Clear interrupt flag for timer 2
    IPC4bits.T3IP = 2;  // Interrupt priority 3
    IEC0bits.T3IE = 1;  // Enable Timer 2 Interrupt

    // Turn on timer 2
    T3CONbits.TON   = 1;
}

void main() {
    //initDataTimer(1);
    //initConfigTimer(1);
    setup_io();

    __builtin_disable_interrupts();
    uart_rx_interrupt(0, 1);
    uart_rx_interrupt(1, 1);
    __builtin_enable_interrupts();

    uartsetup(0, SYS_FREQ, 3000000);
    uartsetup(1, SYS_FREQ, 115200);
    
    ANSELBbits.ANSB3 = 0;
    TRISBbits.TRISB3 = 0;
    PORTBbits.RB3 = ~PORTBbits.RB3;
    int loop = 0;
    while (1) {
        PORTBbits.RB3 = ~PORTBbits.RB3;
        //uartsend(0, 0x55);
        //uartsend(1, 0x55);
        //__delay_ms(1);
    }
}

void __ISR(_TIMER_2_VECTOR, IPL3SOFT)_dataTimerHandler(void) { 
    if (IFS0bits.T2IF) {
        char timeStampHigh = _CP0_GET_COUNT() | 0x70;
        char timeStampLow = _CP0_GET_COUNT() | 0x0F;
        char dataMhorsel[7] = {DAT, FILLER, COM, timeStampHigh, timeStampLow, SMC, EOT};
        int i = 0;
        for(i; i < 7; i++){
            uartsend(0,dataMhorsel[i]);
        }
        TMR2    = 0;
        IFS0bits.T2IF = 0;
        led0_pin = ~led0_pin;
        ANSELBbits.ANSB3 = 0;
        TRISBbits.TRISB3 = 0;
        PORTBbits.RB3 = ~PORTBbits.RB3;
    }
}

void __ISR(_TIMER_3_VECTOR, IPL2SOFT)_configTimerHandler(void) {
    if (IFS0bits.T3IF) {
        char timeStampHigh = _CP0_GET_COUNT() | 0x70;
        char timeStampLow = _CP0_GET_COUNT() | 0x0F;
        char bypassMhorsel[7] = {DAT, FILLER, COM, timeStampHigh, timeStampLow, SMC, EOT};
        int i = 0;
        for(i; i < 7; i++){
            uartsend(0,bypassMhorsel[i]);
        }
        TMR3    = 0;
        IFS0bits.T3IF = 0;
        led1_pin = ~led1_pin;
        ANSELBbits.ANSB2 = 0;
        TRISBbits.TRISB2 = 0;
        PORTBbits.RB2 = ~PORTBbits.RB2;
    }
}

void __ISR(_UART1_RX_VECTOR, IPL5SOFT)_UART1RXHandler(void) {
    if (IFS1bits.U1RXIF) {
        while (IFS1bits.U1RXIF) {
            array[d_index] = uartread(0);
            d_index = (d_index + 1) % 256;
        }
    }
}

void __ISR(_UART2_RX_VECTOR, IPL6SOFT)_UART2RXHandler(void) {
    if (IFS1bits.U2RXIF) {
        while (IFS1bits.U2RXIF) {
            array[d_index] = uartread(0);
            d_index = (d_index + 1) % 256;
        }
    }
}