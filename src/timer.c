#include "timer.h"
#include "common.h"
#include "uart.h"

static uint32_t timer_get();
static void timer_inc();
static void timer_init(uint32_t timeout);

volatile uint32_t CURRENT_TICK = 0;

void timer_sysclk(uint32_t quanta, uint32_t prescaler) {
    if (quanta == 0) {
        quanta = 1;
    }
    timer_init(quanta * prescaler);
}

static void timer_init(uint32_t timeout) {
    SYST_RVR = (timeout - 1);
    SYST_CVR = 0;
    NVIC_SetPriority(SysTick_IRQn, 15);
    SYST_CSR = SYST_CSR_CLKSRC;
    SYST_CSR |= SYST_CSR_TICKINT;
    SYST_CSR |= SYST_CSR_EN;
    __enable_irq();
}

void timer_delay_sec(uint32_t delay) {
    uint32_t delay_start = timer_get();
    while ((timer_get() - delay_start) < delay);
}   

static void timer_inc() {
    CURRENT_TICK++;
}

static uint32_t timer_get() {
    uint32_t current;
    __disable_irq();
   current = CURRENT_TICK;
   __enable_irq();
   return current;
}

void SysTick_Handler() {
    timer_inc();
}