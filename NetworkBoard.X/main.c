#include "ucontroller_config.h"
#include "system_pin.h"
#include <xc.h>
#include <sys/attribs.h>
#include "adc.h"

#define SYS_FREQ 24000000

char array[256];
char d_index = 0;

void initDataTimer() {
    T2CON = 0x0; // Disable timer 2 when setting it up
    TMR2 = 0; // Set timer 2 counter to 0
    IEC0bits.T2IE = 0; // Disable Timer 2 Interrupt

    // Set up the period. Period = PBCLK3 frequency, which is SYS_FREQ / 2, divided by the frequency we want and then divided by 8 for our chosen pre-scaler.
    PR2 = 37500;

    // Set up the pre-scaler
    T2CONbits.TCKPS = 0b110; // Pre-scale of 8

    IFS0bits.T2IF = 0; // Clear interrupt flag for timer 2
    IPC4bits.T2IP = 3; // Interrupt priority 3
    IEC0bits.T2IE = 1; // Enable Timer 2 Interrupt

    // Turn on timer 2
    T2CONbits.TON = 1;
}

void initConfigTimer() {
    T3CON = 0x0; // Disable timer 2 when setting it up
    TMR3 = 0; // Set timer 2 counter to 0
    IEC0bits.T3IE = 0; // Disable Timer 2 Interrupt

    // Set up the period. Period = PBCLK3 frequency, which is SYS_FREQ / 2, divided by the frequency we want and then divided by 8 for our chosen pre-scaler.
    PR3 = 46875;

    // Set up the pre-scaler
    T3CONbits.TCKPS = 0b111; // Pre-scale of 8

    IFS0bits.T3IF = 0; // Clear interrupt flag for timer 2
    IPC4bits.T3IP = 2; // Interrupt priority 3
    IEC0bits.T3IE = 1; // Enable Timer 2 Interrupt

    // Turn on timer 2
    T3CONbits.TON = 1;
}

void main() {
    initDataTimer();
    initConfigTimer(1);
    setup_io();

    __builtin_disable_interrupts();
    uart_rx_interrupt(0, 1);
    uart_rx_interrupt(1, 1);
    __builtin_enable_interrupts();

    uartsetup(0, SYS_FREQ, 1000000);
    uartsetup(1, SYS_FREQ, 1000000);

    ANSELBbits.ANSB3 = 0;
    TRISBbits.TRISB3 = 0;
    while (1) {
        uartsend(0, 0x55);
        __delay_us(100);
    }
}

void __ISR(_TIMER_2_VECTOR, IPL3SOFT)_dataTimerHandler(void) {
    LATBINV = _LATB_LATB7_MASK;
    IFS0bits.T2IF = 0;
    TMR2 = 0;
}

void __ISR(_TIMER_3_VECTOR, IPL2SOFT)_configTimerHandler(void) {
    LATBINV = _LATB_LATB8_MASK;
    IFS0bits.T3IF = 0;
    TMR3 = 0;
}

void __ISR(_UART1_RX_VECTOR, IPL5SOFT)_UART1RXHandler(void) {
    while (IFS1bits.U1RXIF) {
        array[d_index] = uartread(0);
        d_index = (d_index + 1) % 256;
    }
}

void __ISR(_UART2_RX_VECTOR, IPL6SOFT)_UART2RXHandler(void) {
    while (IFS1bits.U2RXIF) {
        array[d_index] = uartread(0);
        d_index = (d_index + 1) % 256;
    }
}