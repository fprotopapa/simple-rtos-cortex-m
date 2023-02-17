#include <stdint.h>

#define SYS_CLOCK 16000000
#define APB1_CLOCK SYS_CLOCK
#define UART_BR 115200

#define PERIPH_BASE 0x40000000UL
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define APB1PERIPH_BASE (PERIPH_BASE + 0x0UL)

#define RCC_AHB1_BASE (AHB1PERIPH_BASE + 0x3800UL)
#define RCC_AHB1ENR_BASE (RCC_AHB1_BASE + 0x30UL)
#define RCC_AHB1ENR (*((volatile uint32_t *)RCC_AHB1ENR_BASE))
#define RCC_GPIOA_EN (1UL << 0)

#define RCC_APB1ENR_BASE (APB1PERIPH_BASE + 0x40UL)
#define RCC_APB1ENR (*((volatile uint32_t *)RCC_APB1ENR_BASE))
#define RCC_USART2_EN (1UL << 17)

#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0UL)
#define GPIOA_MODER_BASE (GPIOA_BASE + 0x0UL) 
#define GPIOA_MODER (*((volatile uint32_t *)GPIOA_MODER_BASE)) 
#define GPIOA_MODER5_1 (1UL << 10)
#define GPIOA_MODER5_2 (1UL << 11) 
#define GPIOA_MODER2_1 (1UL << 4)
#define GPIOA_MODER2_2 (1UL << 5)
#define GPIOA_OUTPUT_BASE (GPIOA_BASE + 0x14UL)
#define GPIOA_OUTPUT (*((volatile uint32_t *)GPIOA_OUTPUT_BASE)) 
#define GPIOA_OUTPUT_5 (1UL << 5)
#define GPIOA_AFRL_BASE (GPIOA_BASE + 0x20UL) 
#define GPIOA_AFRL (*((volatile uint32_t *)GPIOA_AFRL_BASE)) 
#define GPIOA_AFRL2_POS (8U)
#define GPIOA_AF7 (7U)

#define USART2_BASE (APB1PERIPH_BASE + 0x4400UL)
#define USART2_BRR_BASE (USART2_BASE + 0x8UL)
#define USART2_BRR (*((volatile uint32_t *)USART2_BRR_BASE)) 
#define USART2_DIV_FRAC_POS (0UL)
#define USART2_DIV_MAN_POS (4UL)
#define USART2_CR1_BASE (USART2_BASE + 0xCUL)
#define USART2_CR1 (*((volatile uint32_t *)USART2_CR1_BASE)) 
#define USART2_CR1_TE (1UL << 3)
#define USART2_CR1_UE (1UL << 13)
#define USART2_SR_BASE (USART2_BASE + 0x0UL)
#define USART2_SR (*((volatile uint32_t *)USART2_SR_BASE))
#define USART2_SR_TXE (1UL << 7)
#define USART2_DR_BASE (USART2_BASE + 0x4UL)
#define USART2_DR (*((volatile uint32_t *)USART2_DR_BASE))
