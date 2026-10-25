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
    while (1)
    {
        msgqueue = msg_queue_create();
        buffer = queue_create();
        pthread_t producer[5];
        pthread_t consumer[5];
        pthread_t broadcast;
        int MainSocket = create_listingport(8080);
        if (MainSocket == -1)
        {
            printf("Failed to start the server Trying again....\n");
            continue;
        }
        for (int i = 0; i < 5; i++)
        {
            pthread_create(producer[i], NULL, connection_establishing_thrd, (void *)MainSocket);
        }
        printf("Producer thread Inisilized \n");
        for (int i = 0; i < 5; i++)
        {
            pthread_create(consumer[i], NULL, producer_thread, NULL);
        }
        printf("Consumer thread Inisilized \n");
        pthread_create(broadcast, NULL, brodcasting, NULL);
        printf("Brodcasting thread Inisilized");
    }
    return 0;
}