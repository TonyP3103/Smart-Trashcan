#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define LCD_DDR  DDRB
#define LCD_PORT PORTB
#define LED PD7
#define LED_PORT PORTD
#define LED_DDR DDRD
#define RS PB0
#define EN PB1
#define D4 PB2
#define D5 PB3
#define D6 PB4
#define D7 PB5

void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_clear(void);
void lcd_print(const char *str);
void lcd_print_num(int num);
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_display(int dist_hand, int dist_bin, int percent);

#endif
