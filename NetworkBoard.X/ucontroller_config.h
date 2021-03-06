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

#ifndef ucontroller_config_H    /* Guard against multiple inclusion */
#define ucontroller_config_H

void __delay_clk(long clk);
void __delay_us(long us);
void __delay_ms(long ms);
void initDataTimer();
void initConfigTimer();

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
