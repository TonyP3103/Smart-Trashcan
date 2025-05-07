// sensor.c
#include <avr/io.h>
#include <util/delay.h>
#include "sensor.h"

void hcsr04_init(void) {
    SENSOR_DDR |= (1 << Hand_Trig) | (1 << Bin_Trig);         // TRIG1 = PD2, TRIG2 = PD4 là output
    SENSOR_DDR &= ~((1 << Hand_Echo) | (1 << Bin_Echo));      // ECHO1 = PD3, ECHO2 = PD5 là input
}

int measure_distance(uint8_t trig_pin, uint8_t echo_pin) {
    // Gửi xung kích hoạt
    SENSOR_PORT &= ~(1 << trig_pin);
    _delay_us(2);
    SENSOR_PORT |= (1 << trig_pin);
    _delay_us(10);
    SENSOR_PORT &= ~(1 << trig_pin);

    // Chờ ECHO lên HIGH (timeout)
    uint16_t timeout = 30000;
    while (!(PIND & (1 << echo_pin))) {
        if (--timeout == 0) return -1; // Timeout
    }

    // Bắt đầu đo thời gian
    TCNT1 = 0;
    TCCR1B |= (1 << CS11); // Prescaler 8

    // Chờ ECHO xuống LOW (timeout)
    timeout = 30000;
    while (PIND & (1 << echo_pin)) {
        if (--timeout == 0) {
            TCCR1B = 0;
            return -1;
        }
    }

    TCCR1B = 0; // Dừng timer

    unsigned int duration = TCNT1; // Mỗi tick ~0.5us
    int distance = duration  * 0.5 / 29.412 / 2;

    return distance + 1;
}
