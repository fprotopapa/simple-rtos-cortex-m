#include "uart.h"
#include "common.h"
#include <stdio.h>

void uart_write(char c);

int __io_putchar(int ch) {
    uart_write(ch);
    return ch;
}

void uart_init() {
    // Enable clock for GPIOA (USART2)
    RCC_AHB1ENR |= RCC_GPIOA_EN;
    // Set PA2 (TX) to AF
	GPIOA_MODER &= ~GPIOA_MODER2_1;
    GPIOA_MODER |= GPIOA_MODER2_2;
    // Set PA2 to AF7
    GPIOA_AFRL |= (GPIOA_AF7 << GPIOA_AFRL2_POS);
    // Enable UART2 clock
    RCC_APB1ENR |= RCC_USART2_EN;
    // Baudrate 115.108 KBps 8.6875 @16MHz (Div = fck / (16 * BR))
    // Mantis: 8, Fraction: 0.6875 * 16 = 11
    USART2_BRR |= (8 << USART2_DIV_MAN_POS);
    USART2_BRR |= (11 << USART2_DIV_FRAC_POS);
    // Enable TX mode
    USART2_CR1 |= USART2_CR1_TE;
    // Enable UART module
    USART2_CR1 |= USART2_CR1_UE;
}

void uart_write(char c) {
    // Check TX data register
    while(!(USART2_SR & USART2_SR_TXE));
    USART2_DR = (c && 0xFF);
}