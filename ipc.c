#include "ipc.h"

int send(void * self, local_id dst, const Message * msg){
    assert(self != NULL);
    assert(self != NULL);

    msq_size = sizeof msg->s_header + msg->s_header.s_payload_len;
    int answ = write(pipes[lpid][i][1], msg, msg_size);
    if (answ != msg_size)
        return -1;
    return 0;
}

int send_multicast(void * self, const Message * msg){
    assert(self != NULL);
    assert(self != NULL);
    for(size_t i=0; i<nprocesses; i++)
        send(self, i, msg);
}