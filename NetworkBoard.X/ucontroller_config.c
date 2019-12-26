// PIC32MM0064GPM028 Configuration Bit Settings

// 'C' source line config statements

// FDEVOPT
#pragma config SOSCHP = OFF             // Secondary Oscillator High Power Enable bit (SOSC oprerates in normal power mode.)
#pragma config USERID = 0xBEEF          // User ID bits (User ID bits)

// FICD
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config ICS = PGx1               // ICE/ICD Communication Channel Selection bits (Communicate on PGEC1/PGED1)

// FPOR
#pragma config BOREN = BOR0             // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware; SBOREN bit disabled)
#pragma config RETVR = OFF              // Retention Voltage Regulator Enable bit (Retention regulator is disabled)
#pragma config LPBOREN = OFF            // Low Power Brown-out Enable bit (Low power BOR is disabled)

// FWDT
#pragma config SWDTPS = PS1048576       // Sleep Mode Watchdog Timer Postscale Selection bits (1:1048576)
#pragma config FWDTWINSZ = PS25_0       // Watchdog Timer Window Size bits (Watchdog timer window size is 25%)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Watchdog timer is in non-window mode)
#pragma config RWDTPS = PS1048576       // Run Mode Watchdog Timer Postscale Selection bits (1:1048576)
#pragma config RCLKSEL = LPRC           // Run Mode Watchdog Timer Clock Source Selection bits (Clock source is LPRC (same as for sleep mode))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (WDT is disabled)

// FOSCSEL
#pragma config FNOSC = PLL // FRCDIV           // Oscillator Selection bits (Fast RC oscillator (FRC) with divide-by-N)
//#pragma config FPLLMUL = MUL_24
#pragma config PLLSRC = FRC             // System PLL Input Clock Selection bit (FRC oscillator is selected as PLL reference input on device reset)
#pragma config SOSCEN = OFF             // Secondary Oscillator Enable bit (Secondary oscillator (SOSC) is disabled)
#pragma config IESO = OFF               // Two Speed Startup Enable bit (Two speed startup is disabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Selection bit (Primary oscillator is disabled)
#pragma config OSCIOFNC = OFF           // System Clock on CLKO Pin Enable bit (OSCO pin operates as a normal I/O)
#pragma config SOSCSEL = ON             // Secondary Oscillator External Clock Enable bit (External clock is connected to SOSCO pin (RA4 and RB4 are controlled by I/O port registers))
#pragma config FCKSM = CSDCMD           // Clock Switching and Fail-Safe Clock Monitor Enable bits (Clock switching is disabled; Fail-safe clock monitor is disabled)

// FSEC
#pragma config CP = OFF                 // Code Protection Enable bit (Code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <sys/attribs.h>
#include "ucontroller_config.h"

void __delay_us(long us){
    int tWait, tStart;
    tWait = 12*us;
    tStart = _CP0_GET_COUNT();
    while(_CP0_GET_COUNT()-tStart < tWait);
}

void __delay_clk(long clk){
    int tWait, tStart;
    tWait = clk;
    tStart = _CP0_GET_COUNT();
    while(_CP0_GET_COUNT()-tStart < tWait);
}

void __delay_ms(long ms){
    __delay_us(1000*ms);
}

void initDataTimer() {
    T2CON = 0x0; // Disable timer 2 when setting it up
    TMR2 = 0; // Set timer 2 counter to 0
    IEC0bits.T2IE = 0; // Disable Timer 2 Interrupt

    // Set up the period. Period = PBCLK3 frequency, which is SYS_FREQ / 2, divided by the frequency we want and then divided by 8 for our chosen pre-scaler.
    PR2 = 37500;

    // Set up the pre-scaler
    T2CONbits.TCKPS = 0b110; // Pre-scale of 8

    IFS0bits.T2IF = 0; // Clear interrupt flag for timer 2
    IPC4bits.T2IP = 3; // Interrupt priority 3
    IEC0bits.T2IE = 1; // Enable Timer 2 Interrupt

    // Turn on timer 2
    T2CONbits.TON = 1;
}

void initConfigTimer() {
    T3CON = 0x0; // Disable timer 2 when setting it up
    TMR3 = 0; // Set timer 2 counter to 0
    IEC0bits.T3IE = 0; // Disable Timer 2 Interrupt

    // Set up the period. Period = PBCLK3 frequency, which is SYS_FREQ / 2, divided by the frequency we want and then divided by 8 for our chosen pre-scaler.
    PR3 = 46875;

    // Set up the pre-scaler
    T3CONbits.TCKPS = 0b111; // Pre-scale of 8

    IFS0bits.T3IF = 0; // Clear interrupt flag for timer 2
    IPC4bits.T3IP = 2; // Interrupt priority 3
    IEC0bits.T3IE = 1; // Enable Timer 2 Interrupt

    // Turn on timer 2
    T3CONbits.TON = 1;
}