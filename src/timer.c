#include "timer.h"
#include "common.h"
#include "uart.h"

#define TIMER_LOAD_VAL (TIMEOUT_1_SEC - 1)

uint32_t timer_get();
static void timer_inc();

volatile uint32_t CURRENT_TICK=0;

void timer_init() {
    SYST_RVR = TIMER_LOAD_VAL;
    SYST_CVR = 0;
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

uint32_t timer_get() {
    uint32_t current;
    __disable_irq();
   current = CURRENT_TICK;
   __enable_irq();
   return current;
}

void SysTick_Handler() {
    timer_inc();
}