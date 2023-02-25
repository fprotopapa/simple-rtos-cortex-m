#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

void timer_sysclk(uint32_t quanta, uint32_t prescaler);
void timer_delay_sec(uint32_t delay);

#endif // __TIMER_H__