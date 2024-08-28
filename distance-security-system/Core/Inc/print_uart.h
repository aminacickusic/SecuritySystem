#ifndef __PRINT_UART_H_
#define __PRINT_UART_H_

#include "stm32f4xx.h"

void put_char_uart(uint8_t data);
uint8_t get_char_uart();
void print_string_uart(uint8_t * str);
void print_uart(char *str, ... );

#endif
