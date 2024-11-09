#ifndef TASK_SCHED_H
#define TASK_SCHED_H

#include <pico/types.h>

// System number of ticks per millisecond
#define SYS_TICK_PER_MS                 1U

// Some predefined task intervals
#define TASK_INTERVAL_1MS               (1U * SYS_TICK_PER_MS)
#define TASK_INTERVAL_10MS              (10U * SYS_TICK_PER_MS)
#define TASK_INTERVAL_50MS              (50U * SYS_TICK_PER_MS)
#define TASK_INTERVAL_100MS             (100U * SYS_TICK_PER_MS)
#define TASK_INTERVAL_250MS             (250U * SYS_TICK_PER_MS)
#define TASK_INTERVAL_500MS             (500U * SYS_TICK_PER_MS)
#define TASK_INTERVAL_1000MS            (1000U * SYS_TICK_PER_MS)

/*
 * Structure to hold information about a task
 * Note that interval = 0 means that task would
 * run continuously
 * 
 * At runtime, create an array of tasks to be run
 * To add new tasks, simply add new tasks to the table
 * To delay task run from system startup, set last_tick > 0
 */
typedef struct {
    uint16_t interval;      // how often a task should run
    uint32_t next_tick;     // next tick the task should run at
    void (*func)(void);     // task function pointer
} task_t;

void task_sched_config_tasks(task_t *ptr, uint32_t num);
void task_sched_dispatch(void);

#endif  /* TASK_SCHED_H */