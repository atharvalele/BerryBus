#include "system.h"
#include "tick_timer.h"
#include "task_sched.h"
#include "usb_comm.h"

#include <pico/types.h>
#include <pico/stdlib.h>

#include <stdio.h>

// sample tasks
void every_250ms()
{
    static bool led = true;

    system_led_set(led);
    led = !led;
}

void every_500ms()
{
    printf("500ms!\r\n");
}

void every_1000ms()
{
    printf("1000ms!\r\n\r\n");
}

task_t berry_tasks[] = {
    {TASK_INTERVAL_NONE, 0, usb_comm_task},
    {TASK_INTERVAL_250MS, 5000, every_250ms},
    {TASK_INTERVAL_500MS, 0, every_500ms},
    {TASK_INTERVAL_1000MS, 0, every_1000ms}
};

int main()
{
    int rxchar;
    system_init();

    task_sched_config_tasks(berry_tasks, ((sizeof(berry_tasks)) / sizeof(*berry_tasks)));

    while (true) {
        task_sched_dispatch();
        
    }
}
