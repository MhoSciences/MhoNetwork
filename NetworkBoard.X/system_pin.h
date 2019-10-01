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

#define add_led_pin LATBbits.LATB5
#define data_rx_pin LATBbits.LATB6
#define led0_pin    LATBbits.LATB7
#define led1_pin    LATBbits.LATB8
#define sys_pwr_pin LATBbits.LATB13

#define mode_pin    PORTBbits.RB10
#define user_pin    PORTBbits.RB11

void setup_io();

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
