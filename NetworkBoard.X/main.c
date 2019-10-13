#include "ucontroller_config.h"
#include "system_pin.h"
#include <xc.h>
#include <sys/attribs.h>

#define SYS_FREQ 6000000

char array[256];
char d_index = 0;

void main() {
    
    setup_io();

    __builtin_disable_interrupts();
    uart_rx_interrupt(0, 1);
    uart_rx_interrupt(1, 1);
    __builtin_enable_interrupts();

    uartsetup(0, SYS_FREQ, 1000000);
    uartsetup(1, SYS_FREQ, 115200);
    
    int loop = 0;
    while (1) {
        uartsend(0, '0');
        uartsend(1, '0');
        __delay_ms(100);
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