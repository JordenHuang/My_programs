#include <stdio.h>
#include <stdlib.h>

// TODO: write a more clean (or less line) code for the reverse function

typedef struct list{
    int data;
    struct list *next;
}list;


void list_insert_head(list **head, int data){
    list *new_node = (list *)malloc(sizeof(list));
    new_node->data = data;

    if(*head == NULL){
        *head = new_node;
        new_node->next = NULL;
    }
    else{
        new_node->next = *head;
        *head = new_node;
    }
}

void list_delete_head(list **head){
    if(*head != NULL){
        list *next_head = (*head)->next;
        free(head);
        *head = next_head;
    }
    else{
        printf("Nothing to delete!");
    }
}

void list_clear_all(list **head){
    while(*head != NULL){
        list_delete_head(head);
    }
}

void list_print_all(list *head){
    list *cur = head;
    while(cur != NULL){
        if(cur == head){
            printf("[");
        }
        else{
            printf(",");
        }
        printf(" %*d", 2, cur->data);
        cur = cur->next;
    }
    printf("]\n");
}

void list_reverse(list **head){
    list *pre, *cur, *next_cur = *head;

    while(next_cur != NULL){
        pre = cur;
        cur = next_cur;
        next_cur = next_cur->next;

        // reverse the link
        cur->next = pre;
    }
    // set old head's next to null, because it's the tail of the list now
    (*head)->next = NULL;
    
    // assign the new head to the head
    *head = cur;
}


int main(){
    list *head = NULL;
    int i;

    for(i=10; i>=0; i--){
        list_insert_head(&head, i);
    }
    
    printf("Before reverse:\n");
    list_print_all(head);
    
    list_reverse(&head);

    printf("After reverse:\n");
    list_print_all(head);

    list_clear_all(&head);

    return 0;
}