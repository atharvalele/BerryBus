#include "usb_comm.h"

/* USB Buffer size */
#define USB_COMM_BUF_SIZE       500

/* USB comms rx/tx buffers */
static char usb_comm_rxbuf[USB_COMM_BUF_SIZE];
static queue_t usb_comm_rxq;

static char usb_comm_txbuf[USB_COMM_BUF_SIZE];
static queue_t usb_comm_txq;

void usb_comm_init(void)
{
    queue_init(&usb_comm_rxq, sizeof(char), USB_COMM_BUF_SIZE);
    queue_init(&usb_comm_txq, sizeof(char), USB_COMM_BUF_SIZE);
}

int usb_comm_getchar(void)
{
    int c;
    c = stdio_getchar_timeout_us(USB_COMM_TOUT_US);

    return c;
}

void usb_comm_putchar(const char c)
{
    stdio_putchar(c);
}

void usb_comm_task(void)
{
    int rx;
    char c;
    
    // Read data in
    rx = stdio_getchar_timeout_us(0);
    if (rx >= 0) {
        c = (char)rx;
        queue_try_add(&usb_comm_rxq, &c);
    }

    // Write data if any
    if (true == queue_try_remove(&usb_comm_txq, &c)) {
        usb_comm_putchar(c);
    }
}