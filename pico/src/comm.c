#include "comm.h"
#include "usb_comm.h"

#define COMM_RX_BUF_SIZE    500

// Rx state machine variables
static enum COMM_RX_STATE_t comm_rx_state = COMM_RX_IDLE;
static char comm_rx_buf[200];
static uint32_t comm_rx_ptr = 0;

static inline void comm_rx_char(char c)
{
    comm_rx_buf[comm_rx_ptr] = c;
    comm_rx_ptr++;
    if (comm_rx_ptr >= COMM_RX_BUF_SIZE) {
        comm_rx_ptr = 0;
    }
}

static void comm_rx_task(void)
{
    int ret = 0;
    char c = 0;

    switch (comm_rx_state) {
    // Idle - check for available characters
    case COMM_RX_IDLE:
        if (true == usb_comm_available()) {
            comm_rx_state = COMM_RX_WAIT_FOR_START;
        }
    break;

    // Wait for start - check for start character
    case COMM_RX_WAIT_FOR_START:
        ret = usb_comm_getchar();
        if (ret != USB_COMM_NO_DATA) {
            c = (char)ret;

            if (c == COMM_START_OF_FRAME) {
                comm_rx_state = COMM_RX_IN_MSG;
            }
        }
    break;

    // In Message - add characters to frame
    case COMM_RX_IN_MSG:
        ret = usb_comm_getchar();
        if (ret != USB_COMM_NO_DATA) {
            c = (char)ret;

            switch (c) {
            case COMM_ESCAPE_CHAR:
                comm_rx_state = COMM_RX_AFTER_ESCAPE;
            break;

            case COMM_END_OF_FRAME:
                comm_rx_state = COMM_RX_DISPATCH;
            break;
            
            default:
                comm_rx_char(c);
                break;
            }
        }
    break;

    // After escape - handle escape character
    // Add next char to frame and go back to COMM_RX_IN_MSG
    case COMM_RX_AFTER_ESCAPE:
        ret = usb_comm_getchar();
        if (ret != USB_COMM_NO_DATA) {
            c = (char)c;
            comm_rx_char(c);
            
            comm_rx_state = COMM_RX_IN_MSG;
        }
    break;

    // Dispatch - carry out action in the command
    case COMM_RX_DISPATCH:
        // TODO: call appropriate function here
        comm_rx_state = COMM_RX_DONE;
    break;

    // Done - reset state and go to IDLE
    case COMM_RX_DONE:
        comm_rx_ptr = 0;
        comm_rx_state = COMM_RX_IDLE;
    break;

    default:
    break;
    }
}

void comm_task(void)
{
    // run the rx state machine
    comm_rx_task();
}