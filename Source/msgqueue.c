#include "msgqueue.h"
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
struct msg_node
{
    int clinet_id;
    char msg[100];
    struct msg_node *next;
};
typedef struct
{
    pthread_mutex_t lock;
    pthread_cond_t c;
    struct msg_node *head;
    struct msg_node *tail;

} msg_queue;

void msg_node_init(struct msg_node *n)
{
    n->clinet_id = 0;
    memset(n->msg, 0, sizeof(n->msg));
    n->next = NULL;
}
int isempty_msgqueue(msg_queue *list)
{
    if (list->head == NULL)
    {
        return 1;
    }
    return 0;
}
void pushq(msg_queue *list, int clinet_id, char *message)
{
    pthread_mutex_lock(&list->lock);
    struct msg_node *temp = malloc(sizeof(struct msg_node));
    msg_node_init(temp);
    temp->clinet_id = clinet_id;
    snprintf(temp->msg, sizeof(temp->msg), message);
    if (list->head == NULL)
    {
        temp->next = list->head;
        list->head = temp;
        list->tail = temp;
    }
    else
    {
        list->tail->next = temp;
        list->tail = temp;
    }
}
struct msg_node *popq(msg_queue *list)
{
    pthread_mutex_lock(&list->lock);
    while (isempty(list))
    {
        // printf("list is empty cannot dequeue going to sleep....\n");
        pthread_cond_wait(&list->c, &list->lock);
    }
    struct msg_node *temp;
    temp = list->head;
    list->head = list->head->next;
    if (list->head == NULL)
    {
        list->tail = NULL;
    }
    pthread_mutex_unlock(&list->lock);
    return temp;
}
msg_queue *msg_queue_create(void)
{
    msg_queue *q = malloc(sizeof(msg_queue));
    if (q == NULL)
    {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->c, NULL);
    return q;
}
void msg_queue_destroy(msg_queue *q)
{
    if (q == NULL)
        return;
    struct msg_node *current = q->head;
    while (current != NULL)
    {
        struct msg_node *next = current->next;
        free(current);
        current = next;
    }
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->c);
    free(q);
}
int msg_node_client(msg_node *n)
{
    if (n == NULL)
    {
        return -1;
    }
    return n->clinet_id;
}
/*void msg_node_read(msg_node *n)
{
    printf("%s", n->msg);
}*/
void msg_node_write(msg_node *n, const char *message)
{
    if (n != NULL && message != NULL)
    {
        snprintf(n->msg, sizeof(n->msg), "%s", message);
    }
}
const char *msg_node_read(msg_node *n)
{
    if (n == NULL)
    {
        return "";
    }
    return n->msg;
}
