#include "system.h"

#include <hardware/clocks.h>
#include <pico/stdlib.h>

#define ONBOARD_LED                 PICO_DEFAULT_LED_PIN
#define PICO_MAX_SYSCLK             133000000UL

uint32_t PICO_SYS_CLK = 125000000UL;

// init onboard LED
static void system_led_init(void)
{
    gpio_init(ONBOARD_LED);
    gpio_set_dir(ONBOARD_LED, true);
    gpio_put(ONBOARD_LED, false);
}

// set onboard LED status
void system_led_set(bool on)
{
    gpio_put(ONBOARD_LED, on);
}

/* Initialize system */
void system_init(void)
{
    bool clk_sw_status;

    // init onboard LED
    system_led_init();

    // initialize clock to 133MHz
    system_led_set(true);
    clk_sw_status = set_sys_clock_khz((PICO_MAX_SYSCLK/1000UL), true);
    if (true == clk_sw_status) {
        system_led_set(false);
        PICO_SYS_CLK = PICO_MAX_SYSCLK;
    }
}