#include "pwm.h"
#include "system_pin.h"
#include <xc.h>

void setPWM(char pin, long freq, float duty, char state) {
    switch (pin) {
        case 0:
            EX0_setup   =   0;
            EX0_da      =   0;
            EX0_ops     =   11;

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
            break;
        case 1:
            EX1_setup   =   0;
            EX1_da      =   0;
            EX1_ops     =   12;

            CCP5CON1 = 0; // Start with all defaults
            CCP5CON1bits.CLKSEL = 0b000; // Select System Clock  
            CCP5CON1bits.CCSEL = 0; // Set output compare mode      
            CCP5CON1bits.SYNC = 0b00000; // Sync with this module
            CCP5CON1bits.TMRPS = 0b11; // Set 1:64 prescale value to get slowest times
            CCP5CON1bits.MOD = 0b0101; // Double-compare (PWM) output mode
            CCP5PR = ((24000000 / 64) / freq) - 1; // This gives PWM freq =  24.0e6/64/62500 = 6 Hz
            CCP5RA = 0; // Go high at sync event (beginning of PWM cycle)
            // With CCP1RA = 0, duty cycle ratio is CCP1RB / (CCP1PR + 1)
            CCP5RB = duty * CCP5PR; // This gives duty cycle ratio 0.5  (50%)
            CCP5CON1bits.ON = state;
            break;
        case 2:
            EX2_setup   =   0;
            EX2_da      =   0;
            EX2_ops     =   13;

            CCP6CON1 = 0; // Start with all defaults
            CCP6CON1bits.CLKSEL = 0b000; // Select System Clock  
            CCP6CON1bits.CCSEL = 0; // Set output compare mode      
            CCP6CON1bits.SYNC = 0b00000; // Sync with this module
            CCP6CON1bits.TMRPS = 0b11; // Set 1:64 prescale value to get slowest times
            CCP6CON1bits.MOD = 0b0101; // Double-compare (PWM) output mode
            CCP6PR = ((24000000 / 64) / freq) - 1; // This gives PWM freq =  24.0e6/64/62500 = 6 Hz
            CCP6RA = 0; // Go high at sync event (beginning of PWM cycle)
            // With CCP1RA = 0, duty cycle ratio is CCP1RB / (CCP1PR + 1)
            CCP6RB = duty * CCP6PR; // This gives duty cycle ratio 0.5  (50%)
            CCP6CON1bits.ON = state;
            break;
        case 3:
            EX3_setup   =   0;
            EX3_da      =   0;
            EX3_ops     =   14;

            CCP7CON1 = 0; // Start with all defaults
            CCP7CON1bits.CLKSEL = 0b000; // Select System Clock  
            CCP7CON1bits.CCSEL = 0; // Set output compare mode      
            CCP7CON1bits.SYNC = 0b00000; // Sync with this module
            CCP7CON1bits.TMRPS = 0b11; // Set 1:64 prescale value to get slowest times
            CCP7CON1bits.MOD = 0b0101; // Double-compare (PWM) output mode
            CCP7PR = ((24000000 / 64) / freq) - 1; // This gives PWM freq =  24.0e6/64/62500 = 6 Hz
            CCP7RA = 0; // Go high at sync event (beginning of PWM cycle)
            // With CCP1RA = 0, duty cycle ratio is CCP1RB / (CCP1PR + 1)
            CCP7RB = duty * CCP7PR; // This gives duty cycle ratio 0.5  (50%)
            CCP7CON1bits.ON = state;
            break;
        case 4:
            EX4_setup   =   0;
            //EX4_da      =   0;
            EX4_ops     =   15;

            CCP8CON1 = 0; // Start with all defaults
            CCP8CON1bits.CLKSEL = 0b000; // Select System Clock  
            CCP8CON1bits.CCSEL = 0; // Set output compare mode      
            CCP8CON1bits.SYNC = 0b00000; // Sync with this module
            CCP8CON1bits.TMRPS = 0b11; // Set 1:64 prescale value to get slowest times
            CCP8CON1bits.MOD = 0b0101; // Double-compare (PWM) output mode
            CCP8PR = ((24000000 / 64) / freq) - 1; // This gives PWM freq =  24.0e6/64/62500 = 6 Hz
            CCP8RA = 0; // Go high at sync event (beginning of PWM cycle)
            // With CCP1RA = 0, duty cycle ratio is CCP1RB / (CCP1PR + 1)
            CCP8RB = duty * CCP8PR; // This gives duty cycle ratio 0.5  (50%)
            CCP8CON1bits.ON = state;
            break;
        case 5:
            EX5_setup   =   0;
            EX5_da      =   0;
            EX5_ops     =   16;

            CCP9CON1 = 0; // Start with all defaults
            CCP9CON1bits.CLKSEL = 0b000; // Select System Clock  
            CCP9CON1bits.CCSEL = 0; // Set output compare mode      
            CCP9CON1bits.SYNC = 0b00000; // Sync with this module
            CCP9CON1bits.TMRPS = 0b11; // Set 1:64 prescale value to get slowest times
            CCP9CON1bits.MOD = 0b0101; // Double-compare (PWM) output mode
            CCP9PR = ((24000000 / 64) / freq) - 1; // This gives PWM freq =  24.0e6/64/62500 = 6 Hz
            CCP9RA = 0; // Go high at sync event (beginning of PWM cycle)
            // With CCP1RA = 0, duty cycle ratio is CCP1RB / (CCP1PR + 1)
            CCP9RB = duty * CCP9PR; // This gives duty cycle ratio 0.5  (50%)
            CCP9CON1bits.ON = state;
            break;
    }
}