#include "task_sched.h"
#include "tick_timer.h"

#include <stdio.h>

#define MAX_TICK_VAL        UINT32_MAX

static task_t *task_ptr = NULL;
static uint32_t task_num = 0;

static uint32_t curr_tick = 0;

/* Set task_t array ptr */
void task_sched_config_tasks(task_t *ptr, uint32_t num)
{
    if ((NULL == ptr) || (0 == num)) {
        panic("System tasks configured incorrectly! Halting!\r\n");
    }

    task_ptr = ptr;
    task_num = num;
}

/*
 * Main part of the task scheduler
 * Iterate over the list of tasks and run if set interval
 * has elapsed since last time the task ran
 * 
 * Call the function in your main while (1) loop
 */
void task_sched_dispatch(void)
{
    curr_tick = timer_get_current_1ms_tick();

    for (uint32_t t; t < task_num; t++) {
        // Run task if continuous (interval == 0)
        if (0 == task_ptr[t].interval) {
            task_ptr[t].func();
        } else if (curr_tick >= task_ptr[t].next_tick) {
            // execute task
            task_ptr[t].func();

            // update next tick
            task_ptr[t].next_tick += task_ptr[t].interval;
        }
    }
}