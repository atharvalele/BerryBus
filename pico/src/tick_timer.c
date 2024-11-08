#include "tick_timer.h"
#include "system.h"

static volatile uint32_t tick_1ms_cnt = 0;

repeating_timer_t sys_1ms_tick;

/* System 1ms tick */
bool timer_1ms_tick(repeating_timer_t *rt)
{
    tick_1ms_cnt++;

    return true;      // continue repeating
}

uint32_t timer_get_current_1ms_tick(void)
{
    return tick_1ms_cnt;
}

void timer_1ms_tick_init(void)
{
    add_repeating_timer_ms(1, timer_1ms_tick, NULL, &sys_1ms_tick);
}