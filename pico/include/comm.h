#ifndef COMM_H
#define COMM_H

#define COMM_START_OF_FRAME         0x02
#define COMM_END_OF_FRAME           0x03
#define COMM_ESCAPE_CHAR            0x1B

enum COMM_RX_STATE_t {
    COMM_RX_IDLE,
    COMM_RX_WAIT_FOR_START,
    COMM_RX_IN_MSG,
    COMM_RX_AFTER_ESCAPE,
    COMM_RX_DISPATCH,           
    COMM_RX_DONE 
};


void comm_task(void);

#endif /* COMM_H */