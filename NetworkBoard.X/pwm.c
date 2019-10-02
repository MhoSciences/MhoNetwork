#include "pwm.h"
#include <xc.h>

void initpwm(char pin, long freq, float duty, char state) {
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    RPOR1bits.RP8R = 11;

    CCP4CON1 = 0; // Start with all defaults
    CCP4CON1bits.CLKSEL = 0b000; // Select System Clock  
    CCP4CON1bits.CCSEL = 0; // Set output compare mode      
    CCP4CON1bits.SYNC = 0b00000; // Sync with this module
    CCP4CON1bits.TMRPS = 0b11; // Set 1:64 prescale value to get slowest times
    CCP4CON1bits.MOD = 0b0101; // Double-compare (PWM) output mode
    CCP4PR = ((24000000 / 64) / freq) - 1; // This gives PWM freq =  24.0e6/64/62500 = 6 Hz
    CCP4RA = 0; // Go high at sync event (beginning of PWM cycle)
    // With CCP1RA = 0, duty cycle ratio is CCP1RB / (CCP1PR + 1)
    CCP4RB = duty * CCP4PR; // This gives duty cycle ratio 0.5  (50%)
    CCP4CON1bits.ON = state;
}