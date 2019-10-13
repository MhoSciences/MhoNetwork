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

#ifndef uart_H    /* Guard against multiple inclusion */
#define uart_H

void uartsetup(char which, long clock, long baud);
void uart_rx_interrupt(char which, char state);
void uartsend(char fromwhere, char val);
char uartread(char fromwhere);

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
