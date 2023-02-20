#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

void timer_init();
void timer_delay_sec(uint32_t delay);

#endif // __TIMER_H__