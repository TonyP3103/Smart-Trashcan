// sensor.h
#ifndef SENSOR_H
#define SENSOR_H

#define SENSOR_DDR  DDRD
#define SENSOR_PORT PORTD
#define Hand_Trig PD2
#define Hand_Echo PD3
#define Bin_Trig PD4
#define Bin_Echo PD5

#include <stdint.h>

void hcsr04_init(void);
int measure_distance(uint8_t trig_pin, uint8_t echo_pin);

#endif
