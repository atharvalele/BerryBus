#ifndef SYSTEM_H
#define SYSTEM_H

#include <pico/types.h>

extern uint32_t PICO_SYS_CLK;

void system_init(void);
void system_led_set(bool);

#endif /* SYSTEM_H */