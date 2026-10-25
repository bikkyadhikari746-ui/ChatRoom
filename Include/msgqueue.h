#pragma once
#include <pthread.h>
typedef struct msg_node msg_node;
typedef struct msg_queue msg_queue;
msg_queue *msg_queue_create(void);
void msg_queue_destroy(msg_queue *list);
void msg_node_init(struct msg_node *n);
int isempty_msgqueue(msg_queue *list);
void pushq(msg_queue *list, int clinet_id, char *message);
struct msg_node *popq(msg_queue *list);
void msg_node_write(msg_node *n, const char *message);
const char *msg_node_read(msg_node *n);
int msg_node_client(msg_node *n);