#include "ucontroller_config.h"
#include "system_pin.h"
#include <xc.h>
#include <sys/attribs.h>

#define SYS_FREQ 6000000

char array[0x10];
char d_index = 0;

void __delay_us(int us){
    int tWait, tStart;
    tWait = 12*us;
    tStart = _CP0_GET_COUNT();
    while(_CP0_GET_COUNT()-tStart < tWait);
}

void __delay_ms(int ms){
    __delay_us(1000*ms);
}

void main() {
    OSCCON = 0x00000000;
    
    SPLLCONbits.PLLODIV = 0;
    SPLLCONbits.PLLMULT = 6;
    SPLLCONbits.PLLICLK = 1;
    
    setup_io();

    __builtin_disable_interrupts();
    //Int priorities
    IPC13bits.U1RXIP = 6;
    IPC13bits.U1RXIS = 1;
    //Int flags
    IFS1bits.U1RXIF = 0;
    //Int enable/disable
    IEC1bits.U1EIE = 0;
    IEC1bits.U1TXIE = 0;
    IEC1bits.U1RXIE = 1; //Enable int on RX
    //Enable multi-vector interrupts
    //INTCON = 0x00;
    //INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();

    uartsetup(0, SYS_FREQ, 9600);

    int loop = 0;
    while (1) {
        //uartsend(0, '0');
        //for (loop = 0; loop < 60000; loop++);
        add_led_pin = ~add_led_pin;
        data_rx_pin = ~data_rx_pin;
        led0_pin = ~led0_pin;
        led1_pin = ~led1_pin;
        sys_pwr_pin = ~sys_pwr_pin;
        __delay_ms(100);
    }
}

void __ISR(_UART1_RX_VECTOR, IPL6SOFT)_UART1RXHandler(void) {
    if (IFS1bits.U1RXIF) {
        while (IFS1bits.U1RXIF) {
            d_index = U1RXREG;
            IFS1CLR = _IFS1_U1RXIF_MASK;
        }
        if(d_index == '0'){
            data_rx_pin = ~data_rx_pin;
        }
    }
}