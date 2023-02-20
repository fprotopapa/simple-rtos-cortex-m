#include "uart.h"
#include "common.h"

static void uart_write(char c);

void uart_init() {
    // Enable clock for GPIOA (USART2)
    RCC_AHB1ENR |= RCC_GPIOA_EN;
    // Set PA2 (TX) to AF
    GPIOA_MODER |= GPIOA_MODER2_AF;
    // Set PA2 to AF7
    GPIOA_AFRL |= (GPIOA_AF7 << GPIOA_AFRL2_POS);
    // Enable UART2 clock
    RCC_APB1ENR |= RCC_USART2_EN;
    // Baudrate 115.108 kBps 8.6875 @16MHz (Div = fck / (16 * BR))
    // Mantis: 8, Fraction: 0.6875 * 16 = 11
    USART2_BRR = (8 << USART2_DIV_MAN_POS) | (11 << USART2_DIV_FRAC_POS);
    // Clear Control Register
    USART2_CR1 = 0x0;
    // Enable UART module
    USART2_CR1 |= USART2_CR1_UE;
    // Enable TX mode
    USART2_CR1 |= USART2_CR1_TE;
}

static void uart_write(char c) {
    // Check TX data register
    while(!(USART2_SR & USART2_SR_TC));
    USART2_DR = c;
}

size_t uart_print(char* buffer, size_t size) {
    size_t cnt = 0;
    for (; cnt < size; cnt++) {
        uart_write(buffer[cnt]);
    }
    return cnt;
}