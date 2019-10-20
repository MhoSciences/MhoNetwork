#include "adc.h"

void adcsetup(){
    AD1CON1bits.SIDL = 0;
    AD1CON1bits.FORM = 101;
    return;
}