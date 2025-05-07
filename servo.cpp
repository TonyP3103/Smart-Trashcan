#include <avr/io.h>
#include <util/delay.h>
#define SERVO_PORT PORTD
#define SERVO_DDR DDRD
#define SERVO_PIN PD6

void servo_init() {
    SERVO_DDR |= (1 << SERVO_PIN); // PD6 là output
}

// Hàm gửi xung PWM cho servo
void servo_write(uint8_t angle) {
    if (angle > 180) angle = 180;

    if (angle == 0){
      SERVO_PORT |= (1 << SERVO_PIN);
      _delay_us(1000);
      SERVO_PORT &= ~(1 << SERVO_PIN);
      _delay_us(19000);
    }
    else if (angle == 90){
      SERVO_PORT |= (1 << SERVO_PIN);
      _delay_us(2000);
      SERVO_PORT &= ~(1 << SERVO_PIN);
      _delay_us(18000);
    }
    else {
      SERVO_PORT |= (1 << SERVO_PIN);
      _delay_us(1800);
      SERVO_PORT &= ~(1 << SERVO_PIN);
      _delay_us(18200);
    }
}
