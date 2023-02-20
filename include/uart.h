#ifndef __UART_H__
#define __UART_H__

#include <stddef.h>

void uart_init();
size_t uart_print(char* buffer, size_t size);

#endif // __UART_H__