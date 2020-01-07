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

#ifndef pwm_H    /* Guard against multiple inclusion */
#define pwm_H

void setPWM(char pin, long freq, int duty, char state);
void setServo(char pin, char angle);

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
