#ifndef _COMMON_TYPES_H
#define _COMMON_TYPES_H

#define SUCCESS 0
#define LOW 0x0
#define HIGH 0x1
#define OUTPUT 0x1
#define INPUT 0x0

void setPinMode(int pinNumber, int mode);
void digitalPinWrite(int pinNumber, int voltage);

#endif
