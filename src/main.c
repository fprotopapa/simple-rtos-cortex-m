#include "led.h"
#include "uart.h"
#include "timer.h"
#include "common.h"
#include <stdint.h>

void task1();
void task2();
int task1_main();
int task2_main();

int main (void) {
    led_init();
    uart_init();
    timer_sysclk(QUANTA, TIMEOUT_1MSEC);
    led_on();
    volatile uint32_t cnt = 1;
    while (1) {
        if(cnt) {
            task1_main();
        } else {
            task2_main();   
        }  
    }
    return 0;
}
void task1() {
    char buff[] = "Task 1.\n\r";
    uart_print(buff, sizeof(buff));
}

void task2() {
    char buff[] = "Task 2.\n\r";
    uart_print(buff, sizeof(buff));
}

int task1_main() {
    while(1) {
        timer_delay_sec(1);
        task1();
    }
}

int task2_main() {
    while(1) {
        timer_delay_sec(1);
        task2();
    }
}
