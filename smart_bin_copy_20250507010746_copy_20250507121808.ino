#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "sensor.h"
#include "uart.h"
#include "lcd.h"
#include "servo.h"

#define BAUD 9600
#define MYUBRR (F_CPU/8/BAUD - 1)

#define TRIG1 PD2
#define ECHO1 PD3
#define TRIG2 PD4
#define ECHO2 PD5

void setup() {
    uart_init(MYUBRR);
    lcd_init();
    lcd_clear();
    hcsr04_init();
    servo_init();
}

int main(void) {
    setup();

    while (1) {
        int dist1 = measure_distance(TRIG1, ECHO1);
        _delay_ms(60); // Delay giữa 2 lần đo
        int dist2 = measure_distance(TRIG2, ECHO2);
        _delay_ms(60);

        int percent = (dist2 - 10) * 100 / 40;
        if (percent > 100) percent = 100;
        if (percent < 0) percent = 0;

        data_transmit(dist1, dist2);
        lcd_display(dist1, dist2, percent);

        if (dist1 > 0 && dist1 < 10) {
            // Mở nắp trong khi tay còn gần
            do {
                servo_write(0);  // Mở nắp
                _delay_ms(1);    // Giữ PWM 20ms
                dist1 = measure_distance(TRIG1, ECHO1);
                _delay_ms(4);
            } while (dist1 > 0 && dist1 < 10);
            
        }

        // Đóng nắp
            _delay_ms(2000);
            servo_write(90);
            _delay_ms(20);
        
    }
}
