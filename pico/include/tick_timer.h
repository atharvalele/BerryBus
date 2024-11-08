#ifndef TIMER_H
#define TIMER_H

#include <pico/time.h>
#include <pico/types.h>

void timer_1ms_tick_init(void);
uint32_t timer_get_current_1ms_tick(void);

#endif  /* TIMER_H */