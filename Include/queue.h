#ifndef QUEUE_H
#define QUEUE_H

typedef struct node node;
typedef struct queue queue;
struct queue *queue_create(void);
void queue_destroy(queue q);
void queue_init(queue *q);
void node_init(struct node *n);
int isempty(queue *list);
int peek(queue *list);
void enqueue(queue *list, int client_id);
struct node *dequeue(queue *list);
int get_clinetid(node *n);
void free_node(node *n);

#endif
