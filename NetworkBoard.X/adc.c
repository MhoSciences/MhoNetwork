#include <xc.h>
#include "adc.h"
#include "system_pin.h"

void adcsetup(){
    AD1CON1bits.ON = 0;
    
    AD1CON1bits.SIDL = 0;
    AD1CON1bits.MODE12 = 1;
    AD1CON1bits.FORM = 0;
    AD1CON1bits.SSRC = 0;
    AD1CON1bits.ASAM = 0;
    
    AD1CON2bits.VCFG = 0;
    AD1CON2bits.OFFCAL = 0;
    AD1CON2bits.BUFREGEN = 0;
    AD1CON2bits.CSCNA = 0;
    AD1CON2bits.SMPI = 0;
    AD1CON2bits.BUFM = 0;
    
    AD1CON3bits.ADRC = 1;
    AD1CON3bits.EXTSAM = 0;
    AD1CON3bits.SAMC = 10;  //?
    AD1CON3bits.ADCS = 5;   //?
    
    AD1CON5bits.ASEN = 0;
    AD1CON5bits.LPEN = 0;
    AD1CON5bits.BGREQ = 0;
    AD1CON5bits.ASINT = 0;
    AD1CON5bits.WM = 0;
}

int readADC(char pin){
    AD1CON1bits.ON = 0;

    switch (pin){
        case 0:
            EX0_setup   =   1;
            EX0_da      =   1;
            EX0_ops     =   0;
            AD1CHSbits.CH0SA = 4;
            break;
        case 1:
            EX1_setup   =   1;
            EX1_da      =   1;
            EX1_ops     =   0;
            AD1CHSbits.CH0SA = 11;
            break;
        case 2:
            EX2_setup   =   1;
            EX2_da      =   1;
            EX2_ops     =   0;
            AD1CHSbits.CH0SA = 5;
            break;
        case 3:
            EX3_setup   =   1;
            EX3_da      =   1;
            EX3_ops     =   0;
            AD1CHSbits.CH0SA = 6;
            break;
        case 4:
            EX4_setup   =   1;
            EX4_da      =   1;
            EX4_ops     =   0;
            AD1CHSbits.CH0SA = 7;
            break;
        case 5:
            EX5_setup   =   1;
            EX5_da      =   1;
            EX5_ops     =   0;
            AD1CHSbits.CH0SA = 8;
            break;
    }
    
    AD1CON1bits.ON = 1;
    AD1CON1bits.SAMP = 1;
    __delay_us(10);
    AD1CON1bits.SAMP = 0;
    while(AD1CON1bits.DONE == 0);
    return ADC1BUF0;
}