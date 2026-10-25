#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "broadcasting.h"
#include "msgqueue.h"
#include "network.h"
#include "producer.h"
#include "worker.h"
#include "queue.h"
queue *buffer;
msg_queue *msgqueue;
int Active_client[100];
int indexs = 0;
int main()
{
    msgqueue = msg_queue_create();
    buffer = queue_create();
    printf("Main program is working fine ");
    return 0;
}