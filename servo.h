#ifndef SERVO_H
#define SERVO_H

#include <avr/io.h>

void servo_init(void);
void servo_write(uint8_t angle);

#endif
