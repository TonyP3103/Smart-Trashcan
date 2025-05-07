#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"

void uart_init(unsigned int ubrr) {
    UCSR0A = (1 << U2X0);                    // Enable double-speed mode
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << TXEN0);                   // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // 8-bit data, no parity, 1 stop bit
}


void uart_transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void uart_print(const char* str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

void uart_print_num(int num) {
    char buffer[10];
    itoa(num,buffer,10);
    uart_print(buffer);
}

void data_transmit(int a, int b) {
    uart_print("HAND: ");
    if (a < 0)
        uart_print("No Echo");
    else {
        uart_print_num(a);
        uart_print(" cm");
    }

    uart_print(" | BIN: ");
    if (b < 0)
        uart_print("No Echo");
    else {
        uart_print_num(b);
        uart_print(" cm");
    }

    uart_print("\r\n");
}
