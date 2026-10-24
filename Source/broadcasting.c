#include "msgqueue.h"
#include "queue.h"
extern msg_queue msgqueue;
extern Active_client[100];

void *brodcasting(void *args)
{
    while (1)
    {
        struct msg_node *temp;
        temp = popq(&msgqueue);
        int client_id = msg_node_client(temp);
        char *message = msg_node_read(temp);
        char formatted_msg[256];
        nprintf(formatted_msg, sizeof(formatted_msg), "[Client %d]: %s", client_id, message);
        for (int i = 0; i < 100 - 1; i++)
        {
            if ((Active_client[i] == 0) || (Active_client[i] == client_id))
                continue;
            size_t byte_sent = write(Active_client[i], formatted_msg, strlen(formatted_msg));
            if (byte_sent < 0)
            {
                perror("Failed to send data");
            }
        }
        free(temp);
    }
}