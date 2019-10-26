
#include <proc/p32mm0064gpl036.h>

void initADC(void){
    //At this point, not really sure what is meant by input scan. 
    //Could be really important, could not be. 
    
    AD1CON1bits.SIDL = 0x0; //Continues operation in idle mode
    AD1CON1bits.FORM = 0x5; //Output in signed 32-bit integer format
    AD1CON1bits.SSRC = 0x7; //Auto-conversion trigger, internal counter starts conversion
    AD1CON1bits.MODE12 = 0x1; //12-bit ADC operation
    AD1CON1bits.ASAM = 0x1; //Sampling begins following previous
    
    AD1CON2bits.VCFG = 0x0; //Set AV_dd and AV_ss as references
    AD1CON2bits.OFFCAL = 0x0; //Disable offset calibration mode select
    AD1CON2bits.BUFREGEN = 0x0; //Treat ADC register as first in, first out
    AD1CON2bits.CSCNA = 0x0; //Do not scan inputs
    //Might need to be enabled, but not sure as scanning is disabled
    AD1CON2bits.SMPI = 0x0; //Interrupts at the completion for each sample/convert sequence
    AD1CON2bits.BUFM = 0x0; //Buffer configured as 16-bit buffer
    
    AD1CON3bits.ADRC = 0x1; //Clock derived from FRC oscillator
    AD1CON3bits.EXTSAM = 0x0; //ADC stops sampling when SAMP bit is 0
    AD1CON3bits.SAMC = 0x1; //Auto-Sample Time: 1 T_AD
    AD1CON3bits.ADCS = 0x0; //Conversion Clock Selected to 1*T_SRC = T_AD
    
    AD1CON5bits.ASEN = 0x0; //Auto-Scan disabled
    AD1CON5bits.LPEN = 0x0; //Full-power after scan
    AD1CON5bits.BGREQ = 0x0; //Band-gap not enabled by ADC
    AD1CON5bits.ASINT = 0x0; //No interrupt for auto-scan threshold
    AD1CON5bits.WM = 0x0; //Legacy operation, comparison mode is disabled
    AD1CON5bits.CM = 0x3; //Outside Window mode
    //Not entirely clear on the negative/positive input idea. Might be for comparison mode?
    AD1CHSbits.CH0NA = 0x0; //Negative input is AV_ss
    AD1CHSbits.CH0SA = 0x00; //Positive input is AN0
    //AD1CSS might need to be enabled for a single pin
    AD1CSS = 0x00000000; //Skips ANx for input scan
}