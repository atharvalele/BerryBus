#ifndef USB_COMM_H
#define USB_COMM_H

#include <pico/stdio.h>
#include <pico/util/queue.h>

#define USB_COMM_TOUT_US        10

void usb_comm_init(void);
int usb_comm_getchar(void);
void usb_comm_putchar(char c);
void usb_comm_task(void);

#endif  /* USB_COMM_H */