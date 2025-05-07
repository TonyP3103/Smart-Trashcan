#ifndef UART_H
#define UART_H

void uart_init(unsigned int ubrr);
void uart_transmit(char data);
void uart_print(const char* str);
void uart_print_num(int num);
void data_transmit(int a, int b);
#endif
