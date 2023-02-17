//#include "stm32f4xx.h"
#include "led.h"
#include "uart.h"
#include <stdio.h>

int main (void) {
    led_init();
    led_on();
    uart_init();
    while (1) {
        printf("Hello World.\n\r");
    }
    return 0;
}
