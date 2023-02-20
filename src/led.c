#include "led.h"
#include "common.h"



void led_init() {
	// Enable clock
	RCC_AHB1ENR |= RCC_GPIOA_EN;
	// Set PA5 mode to output
	GPIOA_MODER |= GPIOA_MODER5_1;
	GPIOA_MODER &= ~GPIOA_MODER5_2;
}

void led_on() {
	GPIOA_OUTPUT |= GPIOA_OUTPUT_5;
}

void led_off() {
	GPIOA_OUTPUT &= ~GPIOA_OUTPUT_5;
}

void led_toggle() {
	GPIOA_OUTPUT ^= GPIOA_OUTPUT_5;
}