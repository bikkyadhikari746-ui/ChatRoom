#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct node
{
    int clinet_id;
    struct node *next;
    int connection;
};

typedef struct
{
    pthread_mutex_t lock;
    pthread_cond_t c;
    struct node *head;
    struct node *tail;
} queue;

void queue_init(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->c, NULL);
}
int isempty(queue *list)
{
    if (list->head == NULL)
    {
        return 1;
    }
    return 0;
}
int peek(queue *list)
{
    if (isempty(list))
    {
        printf("queue is empty\n");
        return -1;
    }
    return list->head->clinet_id;
}
void enqueue(queue *list, int client_id)
{
    pthread_mutex_lock(&list->lock);
    struct node *temp = malloc(sizeof(struct node));
    node_init(temp);
    temp->clinet_id = client_id;
    if (list->head == NULL)
    {
        temp->next = list->head;
        list->head = temp;
        list->tail = list->head;
    }
    else
    {
        list->tail->next = temp;
        list->tail = temp;
    }
    pthread_cond_signal(&list->c);
    pthread_mutex_unlock(&list->lock);
}
struct node *dequeue(queue *list)
{
    pthread_mutex_lock(&list->lock);
    while (isempty(list))
    {
        // printf("list is empty cannot dequeue going to sleep....\n");
        pthread_cond_wait(&list->c, &list->lock);
    }
    struct node *temp;
    temp = list->head;
    list->head = list->head->next;
    if (list->head == NULL)
    {
        list->tail = NULL;
    }
    pthread_mutex_unlock(&list->lock);
    return temp;
}
void node_init(struct node *n)
{
    n->clinet_id = 0;
    n->next = NULL;
    n->connection = 0;
}
struct queue *queue_create(void)
{
    queue *q = malloc(sizeof(queue));
    if (q == NULL)
    {
        return;
    }
    q->head = NULL;
    q->tail = NULL;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->c, NULL);
    return q;
}
void queue_destroy(queue *q)
{
    if (q == NULL)
        return;
    struct node *temp = q->head;
    while (temp != NULL)
    {
        struct node *next = temp->next;
        free(temp);
        temp = next;
    }
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->c);
    free(q);
}
int get_clinetid(node *n)
{
    if (n == NULL)
    {
        return -1;
    }
    return n->clinet_id;
}
void free_node(node *n)
{
    free(n);
}
