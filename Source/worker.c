#include "queue.h"
#include "msgqueue.h"
#include <stdio.h>
#include <unistd.h>

extern queue *buffer;
extern msg_queue *msgqueue;
extern int Active_client[100];
extern int indexs;

void Inactive(int id)
{
    for (int i = 0; i < 100; i++)
    {
        if (Active_client[i] == id)
        {
            Active_client[i] = 0;
        }
    }
}

void *connection_establishing_thrd(void *args)
{
    while (1)
    {
        if (indexs > 100)
        {
            indexs = 0;
        }
        char buffers[1024];
        struct node *temp = dequeue(buffer);
        if (Active_client[indexs++] > 0)
            continue;
        Active_client[indexs++] = get_clinetid(temp);

        int t = 1;
        while (t)
        {
            int id = get_clinetid(temp);
            size_t bytesize = read(id, buffers, sizeof(buffers) - 1);
            if (bytesize < 0)
                printf("Reading failed\n");
            else if (bytesize == 0)
            {
                printf("client %d id disconnected\n", id);
                t = 0;
                Inactive(id);
            }
            else
            {
                buffers[bytesize] = '\0';
                pushq(msgqueue, id, buffers);
                printf("Message from id %d\n", id);
                printf("%s", buffers);
            }
        }
    }
}