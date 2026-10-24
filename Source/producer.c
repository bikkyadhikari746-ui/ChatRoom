#include "network.h";
#include "queue.h"

extern queue buffer;
void *producer_thread(void *args)
{
    while (1)
    {
        int mainsocket = *(int *)args;
        int client_id = requestaccept(mainsocket);
        if (client_id < 0)
        {
            perror("Connection to clinet is failed in producer thread\n");
        }
        enqueue(&buffer, client_id);
    }
}