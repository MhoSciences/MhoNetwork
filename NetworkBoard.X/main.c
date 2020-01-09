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

    adcsetup();
    uartsetup(0, SYS_FREQ, 750000);
    uartsetup(1, SYS_FREQ, 250000);

    while (1) {
        char loop;
        int data;
        led1_pin = readDI(2);
        data = readADC(1);
        setServo(0, data/32);
        __delay_ms(250);
    }
}

void __ISR(_TIMER_2_VECTOR, IPL4SOFT)_dataCollect(void) {
    
    IFS0bits.T2IF = 0;
    TMR2 = 0;
}

void __ISR(_TIMER_3_VECTOR, IPL5SOFT)_dataAnalyze(void) {
    //Function to analyze data
    IFS0bits.T3IF = 0;
    TMR3 = 0;
}

void __ISR(_EXTERNAL_4_VECTOR, IPL3SOFT) _UserInput(void){
    uartsend(1, SOH);
    uartsend(1, 'C'); //RID0
    uartsend(1, 'P'); //RID1
    uartsend(1, 'U'); //SRID
    uartsend(1, 0x81); //SID0
    uartsend(1, 0x80); //SID1
    uartsend(1, 0x80); //SSID
    uartsend(1, 0x80); //MEM
    uartsend(1, 0x80); //QUEUE
    uartsend(1, 0x80); //FLAG0
    uartsend(1, 0x80); //FLAG1
    uartsend(1, 0x07); //STATUS 

    
    uartsend(1, ETX);
    uartsend(1, 0xFF); //CHK0
    uartsend(1, 0xFF); //CHK1
    uartsend(1, EOT);
    
    IFS0bits.INT4IF = 0;
}

void __ISR(_UART1_RX_VECTOR, IPL2SOFT)_ExtUART(void) { //CPU
    led0_pin = 1;
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
    led0_pin = 0;
}

void __ISR(_UART2_RX_VECTOR, IPL1SOFT)_MHONetwork(void) { //MHO
    led0_pin = 1;
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
    led0_pin = 0;
}
