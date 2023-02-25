#include "kernel.h"
#include "common.h"
#include <stdint.h>

#define KERNEL_NUM_THREADS 3
#define KERNEL_STACK_SIZE 100

typedef struct Tcb_t {
    uint32_t *pt_stack;
    struct tcb *next;
} Tcb_t;

Tcb_t tcbs[KERNEL_NUM_THREADS];
Tcb_t *pt_current;

uint32_t kernel_tcb_stacks[KERNEL_NUM_THREADS][KERNEL_STACK_SIZE];

void kernel_init() {
    
}

void kernel_stack_init(uint32_t stack_pos) {
    uint32_t last_reg = 16;
    uint32_t lr_reg = 3;
    // Stack pointer
    tcbs[stack_pos].pt_stack = &kernel_tcb_stacks[stack_pos][KERNEL_STACK_SIZE - last_reg];
    // Set Thumb mode
    kernel_tcb_stacks[stack_pos][KERNEL_STACK_SIZE - 1] = PSR_THUMB_MODE;
    // Skip PC register 
    // Initialize registers 3 to 16 (For debugging only)
    for (uint32_t i = lr_reg; i <= last_reg; ++i) {
        kernel_tcb_stacks[stack_pos][KERNEL_STACK_SIZE - i] = 0xDEADBEEF;
    }

}

void kernel_add_task(void(*task_0)(void), void(*task_1)(void), void(*task_2)(void)) {
    __disable_irq();
    tcbs[0].next = &tcbs[1];
    tcbs[1].next = &tcbs[2];
    tcbs[2].next = &tcbs[0];

    for (uint32_t i = 0; i < KERNEL_NUM_THREADS; ++i) {
        kernel_stack_init(i);
    }
    // Initialize PC
    kernel_tcb_stacks[0][KERNEL_STACK_SIZE - 2] = (uint32_t)(task_0);
    kernel_tcb_stacks[1][KERNEL_STACK_SIZE - 2] = (uint32_t)(task_1);
    kernel_tcb_stacks[2][KERNEL_STACK_SIZE - 2] = (uint32_t)(task_2);

    pt_current = &tcbs[0];
    __enable_irq();
    
}