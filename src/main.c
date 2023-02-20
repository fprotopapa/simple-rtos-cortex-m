#include "led.h"
#include "uart.h"
#include <stdint.h>

#define DELAY 1000000

void delay (uint32_t time)
{
	while (time--);
}


int main (void) {
    led_init();
    uart_init();
    char buff[] = "Hello World.\n\r";
    while (1) {
        delay (DELAY);
        led_on();
        uart_print(buff, sizeof(buff));
        delay (DELAY);
        led_off();
    }
    return 0;
}

