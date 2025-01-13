#ifndef USB_COMM_H
#define USB_COMM_H

#include <pico/stdio.h>
#include <pico/util/queue.h>

#define USB_COMM_OK             PICO_OK
#define USB_COMM_NO_DATA        PICO_ERROR_NO_DATA
#define USB_COMM_BUF_FULL       PICO_ERROR_INSUFFICIENT_RESOURCES

void usb_comm_init(void);
bool usb_comm_available(void);
int usb_comm_getchar(void);
int usb_comm_putchar(char c);
void usb_comm_task(void);

#endif  /* USB_COMM_H */