#include <stdint.h>

#define SYS_CLOCK 16000000U
#define TIMEOUT_1SEC SYS_CLOCK
#define TIMEOUT_1MSEC (SYS_CLOCK / 1000U)
#define QUANTA 10
#define APB1_CLOCK SYS_CLOCK
#define UART_BR 115200

#define PERIPH_BASE 0x40000000UL
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define APB1PERIPH_BASE (PERIPH_BASE + 0x0UL)

#define RCC_BASE (AHB1PERIPH_BASE + 0x3800UL)
#define RCC_AHB1ENR_BASE (RCC_BASE + 0x30UL)
#define RCC_AHB1ENR (*((volatile uint32_t *)RCC_AHB1ENR_BASE))
#define RCC_GPIOA_EN (1UL << 0)

#define RCC_APB1ENR_BASE (RCC_BASE + 0x40UL)
#define RCC_APB1ENR (*((volatile uint32_t *)RCC_APB1ENR_BASE))
#define RCC_USART2_EN (1UL << 17) 

#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0UL)
#define GPIOA_MODER_BASE (GPIOA_BASE + 0x0UL) 
#define GPIOA_MODER (*((volatile uint32_t *)GPIOA_MODER_BASE)) 
#define GPIOA_MODER5_1 (1UL << 10)
#define GPIOA_MODER5_2 (1UL << 11) 
#define GPIOA_MODER2_AF (2UL << 4)
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
#define USART2_SR_TC (1UL << 6)
#define USART2_SR_TXE (1UL << 7)
#define USART2_DR_BASE (USART2_BASE + 0x4UL)
#define USART2_DR (*((volatile uint32_t *)USART2_DR_BASE))

#define SYST_CSR_EN (1UL << 0)
#define SYST_CSR_TICKINT (1UL << 1)
#define SYST_CSR_CLKSRC (1UL << 2)
#define SYST_CSR_CNTFLAG (1UL << 16)
#define SYST_CSR (*((volatile uint32_t *)0xE000E010))
#define SYST_RVR (*((volatile uint32_t *)0xE000E014))
#define SYST_CVR (*((volatile uint32_t *)0xE000E018))

#define PSR_THUMB_MODE (1UL << 24)

__attribute__((always_inline)) static inline void __enable_irq(void)
{
  __asm volatile ("cpsie i" : : : "memory");
}

__attribute__((always_inline)) static inline void __disable_irq(void)
{
  __asm volatile ("cpsid i" : : : "memory");
}

/* CMSIS NVIC Set Priority*/

typedef struct
{
  volatile const uint32_t CPUID;
  volatile uint32_t ICSR;
  uint32_t RESERVED0;
  volatile uint32_t AIRCR;
  volatile uint32_t SCR;
  volatile uint32_t CCR;
  uint32_t RESERVED1;
  volatile uint32_t SHP[2U];
  volatile uint32_t SHCSR;
} SCB_Type;

#define __NVIC_PRIO_BITS 4U

#define SCS_BASE (0xE000E000UL)
#define SCB_BASE (SCS_BASE +  0x0D00UL)
#define SCB ((SCB_Type *) SCB_BASE )

typedef enum
{
/******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
} IRQn_Type;

static inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    SCB->SHP[(((uint32_t)(int32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
}