#include "system.h"
#include "tick_timer.h"
#include "task_sched.h"
#include "usb_comm.h"
#include "comm.h"

#include <pico/types.h>
#include <pico/stdlib.h>

#include <stdio.h>

task_t berry_tasks[] = {
    // USB Serial comms task, run continuously
    {TASK_INTERVAL_NONE, 0, usb_comm_task},

    // Communications task: start 50ms post system init, run continously
    {TASK_INTERVAL_NONE, 50, comm_task}
};

int main()
{
    system_init();

    task_sched_config_tasks(berry_tasks, ((sizeof(berry_tasks)) / sizeof(*berry_tasks)));

    while (true) {
        task_sched_dispatch();     
    }
}
