/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef system_pins_H    /* Guard against multiple inclusion */
#define system_pins_H

#define led0_pin    LATBbits.LATB6
#define led1_pin    LATBbits.LATB7
#define led2_pin    LATBbits.LATB8

#define sys_pwr_pin LATBbits.LATB11
#define data_rx_pin LATBbits.LATB5
#define mode_pin    PORTBbits.RB10
#define user_pin    PORTAbits.RA4

#define EX0_setup   TRISBbits.TRISB2
#define EX0_da      ANSELBbits.ANSB2
#define EX0_ops     RPOR1bits.RP8R
#define EX0_o       LATBbits.LATB2
#define EX0_i       PORTBbits.RB2

#define EX1_setup   TRISBbits.TRISB3
#define EX1_da      ANSELBbits.ANSB3
#define EX1_ops     RPOR2bits.RP9R
#define EX1_o       LATBbits.LATB3
#define EX1_i       PORTBbits.RB3

#define EX2_setup   TRISAbits.TRISA2
#define EX2_da      ANSELAbits.ANSA2
#define EX2_ops     RPOR0bits.RP3R
#define EX2_o       LATAbits.LATA2
#define EX2_i       PORTAbits.RA2

#define EX3_setup   TRISAbits.TRISA3
#define EX3_da      ANSELAbits.ANSA3
#define EX3_ops     RPOR0bits.RP4R
#define EX3_o       LATAbits.LATA3
#define EX3_i       PORTAbits.RA3

#define EX4_setup   TRISBbits.TRISB4
#define EX4_da      ANSELBbits.ANSB4
#define EX4_ops     RPOR2bits.RP10R
#define EX4_o       LATBbits.LATB4
#define EX4_i       PORTBbits.RB4

#define EX5_setup   TRISBbits.TRISB13
#define EX5_da      ANSELBbits.ANSB13
#define EX5_ops     RPOR3bits.RP15R
#define EX5_o       LATBbits.LATB13
#define EX5_i       PORTBbits.RB13

void setup_io();
void setD0(char pin, char value);
char readDI(char pin);

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
