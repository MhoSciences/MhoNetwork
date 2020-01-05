#include "ucontroller_config.h"
#include "delimiter_definitions.h"
#include "system_pin.h"
#include <xc.h>
#include <sys/attribs.h>
#include "adc.h"

#define SYS_FREQ 24000000

char cpuMhorcel[8][256];
char mhoMhorcel[8][256];
char cpuIndex = 0;
char mhoIndex = 0;
char cpuDataFlag = 0;
char mhoDataFlag = 0;

void main() {
    initDataTimer();
    initConfigTimer(1);
    setup_io();

    __builtin_disable_interrupts();
    //uart_rx_interrupt(0, 1);
    //uart_rx_interrupt(1, 1);
    __builtin_enable_interrupts();

    uartsetup(0, SYS_FREQ, 115200);
    uartsetup(1, SYS_FREQ, 115200);

    while (1) {
        //        setPWM(0, 1000, 0.1, 1);
        //        setPWM(1, 1000, 0.2, 1);
        //        setPWM(2, 1000, 0.3, 1);
        //        setPWM(3, 1000, 0.4, 1);
        //        setPWM(4, 1000, 0.5, 1);
        led2_pin = ~led2_pin;
        __delay_ms(500);
    }
}

void __ISR(_TIMER_2_VECTOR, IPL4SOFT)_dataCollect(void) {
    led0_pin = 1;
    __delay_ms(5);
    IFS0bits.T2IF = 0;
    TMR2 = 0;
    led0_pin = 0;
}

void __ISR(_TIMER_3_VECTOR, IPL5SOFT)_dataAnalyze(void) {
    led1_pin = 1;
__delay_ms(5);
    IFS0bits.T3IF = 0;
    TMR3 = 0;
    led1_pin = 0;
}

void __ISR(_EXTERNAL_4_VECTOR, IPL3SOFT) _UserInput(void){
    while(user_pin == 0){
        led0_pin = 1;
        led1_pin = 1;
        led2_pin = 1;
    }
    IFS0bits.INT4IF = 0;
}

void __ISR(_UART1_RX_VECTOR, IPL2SOFT)_ExtUART(void) { //CPU
    if (mode_pin) {
        while (IFS1bits.U1RXIF) {
            cpuMhorcel[0][cpuIndex] = uartread(0);
            if (cpuMhorcel[0][cpuIndex] == EOT) {
                cpuDataFlag = 1;
                cpuIndex = 0;
            }
            cpuIndex++;
        }
    } else { // If mode is pass through device
        uartsend(1, uartread(0));
    }
}

void __ISR(_UART2_RX_VECTOR, IPL1SOFT)_MHONetwork(void) { //MHO
    if (mode_pin) {
        while (IFS1bits.U2RXIF) {
            mhoMhorcel[0][mhoIndex] = uartread(1);
            if (mhoMhorcel[0][mhoIndex] == EOT) {
                mhoDataFlag = 1;
                mhoIndex = 0;
            }
            mhoIndex++;
        }
    } else { // If mode is pass through device
        uartsend(0, uartread(1));
    }
}
