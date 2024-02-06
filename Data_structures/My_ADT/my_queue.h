
#ifndef _MY_QUEUE_H_
#define _MY_QUEUE_H_

/*/
 * Not store the data in the queue, but store the address of the data
 *
 * 
/*/

struct queue_node {
    void *data;
    char *type_info;
    struct queue_node *tail;
    struct queue_node *next_node;
};

typedef struct queue_node queue;

void queue_enqueue(queue **head, void *data);

void *queue_dequeue(queue **head);

/*/
 * type_info is not impelemented yet
 * 
 * 
/*/

int queue_length(queue *head);

int queue_empty(queue *head);

void queue_clear(queue **head);

#endif