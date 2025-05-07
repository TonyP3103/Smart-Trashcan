#include "lcd.h"

void lcd_enable() {
    LCD_PORT |= (1 << EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << EN);
    _delay_us(6);
}

void lcd_send_nibble(uint8_t nibble) {
    LCD_PORT &= ~((1 << D4) | (1 << D5) | (1 << D6) | (1 << D7));
    if (nibble & 0x01) LCD_PORT |= (1 << D4);
    if (nibble & 0x02) LCD_PORT |= (1 << D5);
    if (nibble & 0x04) LCD_PORT |= (1 << D6);
    if (nibble & 0x08) LCD_PORT |= (1 << D7);
    lcd_enable();
}

void lcd_send_byte(uint8_t data, uint8_t rs) {
    if (rs)
        LCD_PORT |= (1 << RS);
    else
        LCD_PORT &= ~(1 << RS);

    lcd_send_nibble(data >> 4);
    _delay_us(50);
    lcd_send_nibble(data & 0x0F);
    _delay_us(50);
}

void lcd_command(uint8_t cmd) {
    lcd_send_byte(cmd, 0);
    if (cmd == 0x01 || cmd == 0x02)
        _delay_us(2000);
}

void lcd_data(uint8_t data) {
    lcd_send_byte(data, 1);
}

void lcd_init() {
    LED_DDR |= (1 << LED);
    LCD_DDR |= (1 << RS) | (1 << EN) | (1 << D4) | (1 << D5) | (1 << D6) | (1 << D7);
    _delay_us(2000);

    lcd_send_nibble(0x03);
    _delay_us(5000);
    lcd_send_nibble(0x03);
    _delay_us(100);
    lcd_send_nibble(0x03);
    _delay_us(100);
    lcd_send_nibble(0x02);  // 4-bit mode

    lcd_command(0x28); // 4-bit, 2 dòng, font 5x8
    lcd_command(0x0C); // Hiển thị, tắt con trỏ
    lcd_command(0x06); // Tăng con trỏ
    lcd_command(0x01); // Xoá màn hình
    _delay_us(2000);
}

void lcd_clear() {
    lcd_command(0x01);
    _delay_us(2000);
}

void lcd_print(const char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

void lcd_print_num(int num) {
    char buffer[10];
    itoa(num, buffer, 10);
    lcd_print(buffer);
}

void lcd_gotoxy(uint8_t x, uint8_t y) {
    if (x > 15) x = 15;
    if (y > 1) y = 1;
    uint8_t addr = (y == 0) ? 0x00 : 0x40;
    lcd_command(0x80 | (addr + x));
}

void lcd_display(int dist_hand, int dist_bin, int percent) {
    lcd_clear();
    
    if (dist_bin < 10) {
        lcd_gotoxy(5, 0);
        lcd_print("FULL!");
        lcd_gotoxy(3, 1);
        lcd_print("Trash out!");
        LED_PORT |= (1<<LED);
    }
    else if (dist_bin >= 10 && dist_bin < 51) {
        int percent =  100 - ((dist_bin - 10) * 100 / 40);  // Giả sử 10cm = đầy, 50cm = rỗng

        lcd_gotoxy(0, 0);
        lcd_print("Capacity: ");
        lcd_gotoxy(0, 1);
        lcd_print_num(percent);
        lcd_print("%");
        LED_PORT &= ~(1<<LED);
    }
    else {
        lcd_gotoxy(5, 0);
        lcd_print("ERROR!");
        LED_PORT &= ~(1<<LED);
    }
    _delay_us(2500);
}
