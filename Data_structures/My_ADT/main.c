#include <stdio.h>
#include <stdlib.h>

// #include "my_stack.h"
#include "my_queue.h"

int main(){
    queue *head=NULL, *cur;
    char *str[10];
    int num[5];
    int n = 0;
    void *void_ptr;    

    while (n < 5){
        // printf("Enter the data (int): ");
        // scanf("%d", &num[n]);

        printf("Enter the data (str): ");
        scanf("%s", &str[n]);

        void_ptr = &str[n];
        printf("ptr: %p\n", void_ptr);
        queue_enqueue(&head, void_ptr);
        n++;
    }

    printf("length: %d\n", queue_length(head));
    
    cur = head;
    while (cur != NULL){
        printf("inside: %s\n", (char *)(cur->data));
        cur = cur->next_node;
    }
    
    printf("empty? %d\n", queue_empty(head));
    printf("length: %d\n", queue_length(head));

    void_ptr = queue_dequeue(&head);
    
    printf("The poped data: %s\n", (char *)void_ptr);

    printf("after dequeue one,  empty? %d\n", queue_empty(head));
    printf("length: %d\n", queue_length(head));

    queue_clear(&head);

    printf("after clear, empty? %d\n", queue_empty(head));
    printf("length: %d\n", queue_length(head));

    return 0;
}