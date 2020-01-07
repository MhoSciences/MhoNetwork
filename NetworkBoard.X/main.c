#include "ucontroller_config.h"
#include "delimiter_definitions.h"
#include "system_pin.h"
#include <xc.h>
#include <sys/attribs.h>
#include "adc.h"

#define SYS_FREQ 24000000

#define Mhorsel_Length 8
#define Mhorsel_Depth 256
#define Min_Mhorsel_Header_Size 17 

char cpuMhorcel[Mhorsel_Length][Mhorsel_Depth];
char mhoMhorcel[Mhorsel_Length][Mhorsel_Depth];
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

//Reads all inputs and stores data in buffer until requested by outside agent
void __ISR(_TIMER_2_VECTOR, IPL4SOFT)_dataCollect(void) {
    led0_pin = 1;
    __delay_ms(5);
    IFS0bits.T2IF = 0;
    //Data parsing here?
    TMR2 = 0;
    led0_pin = 0;
}

//Name: _dataAnalyze
//Purpose: Parse the individual packets in the 
//Inputs: None
//Outputs: None
void __ISR(_TIMER_3_VECTOR, IPL5SOFT)_dataAnalyze(void) {
    led1_pin = 1;
    int i;
    for(i = 0; i < Mhorsel_Length; i++){
        int j = 0;
        //Starting from the beginning, attempt to find the SOH Byte value
        while((j < Mhorsel_Depth) && (mhoMhorcel[i][j] != SOH)){
            j++;
        }
        //Check that the minimum number of values are present for the header, if so parse normally
        if((Mhorsel_Depth - j) >= Min_Mhorsel_Header_Size){
            //Found SOH, get RID, SID, MEM, QUE, MSGCNT, FLAG, INSTR from packet
            char offsetVal = 8;
            //Get full 3 Byte RID value from packet
            int RID = (mhoMhorcel[i][j+1] << 2*offsetVal) + (mhoMhorcel[i][j+2] << offsetVal) + mhoMhorcel[i][j+3];
            //Get full 3 Byte SID value from packet
            int SID = (mhoMhorcel[i][j+4] << 2*offsetVal) + (mhoMhorcel[i][j+5] << offsetVal) + mhoMhorcel[i][j+6];
            //Get MEM Byte value from packet
            char MEM = mhoMhorcel[i][j+7];
            //Get QUE Byte value from packet
            char QUE = mhoMhorcel[i][j+8];
            //Get MSGCNT Byte value from packet
            char MSGCNT = mhoMhorcel[i][j+9];
            //Get full 2 Byte FLAG value
            int FLAG = (mhoMhorcel[i][j+10] << offsetVal) + mhoMhorcel[i][j+11];
            //Get INST Byte value
            char INST = mhoMhorcel[i][j+12];
            //Prepare for data gathering by incrementing j to past the INST value
            j += 13;
            //Create an array that should be able to hold all potential data bytes
            char DATA[Mhorsel_Depth-j-3];
            //Define a data field offset value to be added to position
            int k;
            //For all data potentially in data field
            for(k = 0; (k < Mhorsel_Depth-j-3) && (mhoMhorcel[i][j+k] != ETX); k++){
                DATA[k] = mhoMhorcel[i][j+k]; 
            }
            //Update the mhoMhorcel array index with data offset
            j += k;
            //Get full 2 Byte CHKSUM value
            int CHKSUM = (mhoMhorcel[i][j+1] << offsetVal) + mhoMhorcel[i][j+2];
            //Check EOT
            if(mhoMhorcel[i][j+3] != EOT){
                //Raise flag? -Joe
            }
            else{
                //If not able to parse normally, set flags/errors? -Joe
            }
        }
    }
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

//Name: _ExtUART
//Purpose: Send/receive packets from any non-Mhodule device via UART
//Inputs: None
//Outputs: None
void __ISR(_UART1_RX_VECTOR, IPL2SOFT)_ExtUART(void) { //CPU
    if (mode_pin) {
        while (IFS1bits.U1RXIF) {
            cpuMhorcel[0][cpuIndex] = uartread(0); //Currently only places a new Mhorcel into the first column of the array. By design? -Joe
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

//Name: _MHONetwork
//Purpose: Send packets to other Mhodules over the single wire via UART
//Inputs: None
//Outputs: None
void __ISR(_UART2_RX_VECTOR, IPL1SOFT)_MHONetwork(void) { //MHO
    if (mode_pin) {
        while (IFS1bits.U2RXIF) {
            mhoMhorcel[0][mhoIndex] = uartread(1); //Currently only places a new Mhorcel into the first column of the array. By design? -Joe
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
