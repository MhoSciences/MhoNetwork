// PIC32MM0064GPL036 Configuration Bit Settings

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

#define sys_pwr_pin LATBbits.LATB9
#define data_rx_pin LATCbits.LATC9
#define hardware_add (PORTA & 0x0F)

char array[0x10];
char d_index = 0;

void setup_io() {
    //Input Setup RA0-RA3 are address pins RA4 is Input
    TRISA = 0xFF;
    ANSELA = 0x00;

    //Output Setup RB9 is System Power RC9 is Data Interrupt Flag
    TRISBbits.TRISB9 = 0;
    TRISCbits.TRISC9 = 0;
}

void __ISR(_UART1_RX_VECTOR, IPL6SOFT)_UART1RXHandler(void) {
    if (IFS1bits.U1RXIF) {
        while (IFS1bits.U1RXIF) {
            d_index = U1RXREG;
            U1RXREG = 0;
            IFS1CLR = _IFS1_U1RXIF_MASK;
            //sys_pwr_pin = U1STAbits.URXDA;
        }
        data_rx_pin = ~data_rx_pin;
    }
}

void main() {
    setup_io();

    initPwm();

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

    uartsetup(0, 6000000, 9600);

    int loop = 0;
    while (1) {
        uartsend(0, '0');
        for (loop = 0; loop < 60000; loop++);
    }
}

