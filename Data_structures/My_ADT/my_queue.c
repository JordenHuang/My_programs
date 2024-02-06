#include <stdio.h>
#include <stdlib.h>

#include "my_queue.h"


/*/
 * Not store the data in the queue, but store the address of the data
 *
 * 
/*/


void queue_enqueue(queue **head, void *data){
    queue *new_node = malloc(sizeof(queue));
    new_node->data = data;
    new_node->tail = NULL;
    new_node->next_node = NULL;
    new_node->type_info = "None";

    // if head is null
    if(*head == NULL){
        // printf("null\n");
        *head = new_node;
        (*head)->tail = new_node;
        // printf("null leave\n");
        return;
    }

    // if only head
    if ((*head)->next_node == NULL){
        // printf("only head\n");
        (*head)->next_node = new_node;
        (*head)->tail = new_node;
        // printf("only head leave\n");
        return;
    }

    // printf("else\n");
    (*head)->tail->next_node = new_node;
    (*head)->tail = new_node;
    // printf("else leave\n");
}


void *queue_dequeue(queue **head){
    /* This function doesn't check if the queue is empty or not */

    queue *poped_node = *head;
    void *poped_data = (*head)->data;

    // store the tail's address to the new head
    if ((*head)->next_node != NULL) {
        (*head)->next_node->tail = (*head)->tail;
    }

    // detach the current head
    *head = (*head)->next_node;
    free(poped_node);

    return poped_data;
}


int queue_length(queue *head){
    int length = 0;
	queue *cur = head;
	
	while (cur != NULL){
		length++;
		cur = cur->next_node;
        
	}
	
	return length;
}


int queue_empty(queue *head){
    /* 0: not empty, 1: empty */
    if (head == NULL) return 1;
    return 0;
}


void queue_clear(queue **head){
    while (!queue_empty(*head)){
        queue_dequeue(head);
    }
}