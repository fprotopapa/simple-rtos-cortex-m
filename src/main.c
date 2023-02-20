#include "led.h"
#include "uart.h"
#include "timer.h"
#include <stdint.h>

int main (void) {
    led_init();
    uart_init();
    timer_init();
    char buff[] = "Hello World.\n\r";
    uart_print(buff, sizeof(buff));
    while (1) {
        timer_delay_sec(1);
        led_on();
        uart_print(buff, sizeof(buff));
        timer_delay_sec(1);
        led_off();
    }
    return 0;
}

