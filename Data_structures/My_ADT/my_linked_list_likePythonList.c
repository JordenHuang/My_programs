#include <stdio.h>
#include <stdlib.h>

//TODO: add if malloc return NULL, then print "CAN'T create new node"

/* (+ means not yet finish)
empty(): check if the list is empty or not (the node after list head is NULL means empty)
list_length(): the length of the list

append(): append at the end of the list
insert(): insert(): insert in the specified position (the first element of the list is at position 1)

pop(): pop the element at the end of the list
remove_list(): remove the specified position's element

+index()
+sort()

print_all(): print all elements in the list

clear(): remove all the element in the list
commands(): show all commands
exit_program(): clear() and exit the program
*/


struct list_node{
    int num;
    struct list_node *next_node;
};

typedef struct list_node list;


int empty(list *list_head){
    if(list_head->next_node == NULL) return 1;  // return 1 means it's empty
    else return 0;
}


int list_length(list *list_head){
    int length=0;
    list *pre=list_head;
    list *current=pre->next_node;

    if(empty(list_head)) return length;

    length++;  // the first node (because not list is not empty, and current is at this node)
    while(current->next_node != NULL){  // move to the next node and add 1 to the length
        pre = current;
        current = current->next_node;
        length++;
    }

    return length;
}


void append(list *list_head, int data){
    list *pre=list_head;
    list *current=pre->next_node;

    // create a new node and add data into it
    list *new_node = malloc(sizeof(list));
    new_node->num = data;

    // walk to the end of the list
    while(current != NULL){
        pre = current;
        current = current->next_node;
    }

    // insert at the end
    pre->next_node = new_node;
    new_node->next_node = NULL;
}


void insert(list *list_head, int data, int target_pos){
    list *pre=list_head;
    list *current=pre->next_node;
    int current_pos = 1;

    // create a new node and add data into it
    list *new_node = malloc(sizeof(list));
    new_node->num = data;

    // insert the data at the end for target position equal to or bigger than the list length
    if(target_pos > list_length(list_head)){
        while(current != NULL){
            pre = current;
            current = current->next_node;
        }
        pre->next_node = new_node;
        new_node->next_node = NULL;
    }
    // else insert at the specified position
    else{
        while(current_pos != target_pos){
            pre = current;
            current = current->next_node;
            current_pos++;
        }
        pre->next_node = new_node;
        new_node->next_node = current;
    }
}


int pop(list *list_head){
    list *pre=list_head;
    list *current=pre->next_node;
    int poped_data;

    // walk to the end of the list
    while(current->next_node != NULL){
        pre = current;
        current = current->next_node;
    }

    // pop the last data
    poped_data = current->num;
    pre->next_node = NULL;

    // free the node
    free(current);

    return poped_data;
}


int remove_list(list *list_head, int target_pos){
    list *pre=list_head;
    list *current=pre->next_node;
    int removed_data, current_pos=1;

    // remove the data at the end for target position equals to or bigger than the list length
    if(target_pos >= list_length(list_head)){
        while(current->next_node != NULL){
            pre = current;
            current = current->next_node;
        }
        removed_data = current->num;
        pre->next_node = NULL;
    }
    // else remove data at the specified position
    else{
        while(current_pos != target_pos){
            pre = current;
            current = current->next_node;
            current_pos++;
        }
        removed_data = current->num;
        pre->next_node = current->next_node;
    }

    free(current);

    return removed_data;
}

void print_all(list *list_head){
    list *pre=list_head;
    list *current=pre->next_node;

    printf("[ ");

    while(current != NULL){
        if(current->next_node != NULL){
            printf("%d, ", current->num);
        }
        else{
            printf("%d ", current->num);
        }
        pre = current;
        current = current->next_node;
    }

    printf("]");
}


void clear(list *list_head){
    list *pre=list_head->next_node;  // the node after list head
    list *current=pre->next_node;  // the second node after list head

    list_head->next_node = NULL;

    while(current != NULL){
        free(pre);
        pre = current;
        current = current->next_node;
    }
    free(pre);
}


void commands(){
    printf("Commands:\n");
    printf("1 for append(): append at the end of the list\n");
    printf("2 for insert(): insert in the specified position (the first element of the list is at position 1)\n");
    printf("3 for pop(): pop the element in the end of the list\n");
    printf("4 for remove_list(): remove the element in the specified position (the first element of the list is at position 1)\n");
    printf("5 for print_all(): print all elements in the list\n");
    printf("6 for clear(): clear all elements in the list\n");
    printf("7 for list_length(): show the list length\n");
    printf("10 for commands(): show all commands\n");
    printf("0 for exit the program\n");
}



int main(){
    list *list_head;
    list_head->next_node=NULL;

    int user_choise, data, target_pos;

    commands();

    while(1){
        printf("\nEnter the command: ");
        scanf("%d%*c", &user_choise);

        switch(user_choise){
            case 1:
            printf("Enter data to append\n>>");
            scanf("%d", &data);
            append(list_head, data);
            print_all(list_head);
            break;

            case 2:
            printf("Enter data to insert\n>>");
            scanf("%d", &data);
            printf("Enter position (1 ~ list_length, list_length is now: %d)\n>>", list_length(list_head));
            scanf("%d", &target_pos);
            if(target_pos < 1){
                printf("Invalid position!!");    
                break;
            }
            insert(list_head, data, target_pos);
            print_all(list_head);
            break;

            case 3:
            if(!empty(list_head)){  // if the list has data to pop (means not empty)
                data = pop(list_head);
                printf("The poped data is: %d", data);
            }
            else printf("The list is empty, nothing to pop");
            break;

            case 4:
            if(!empty(list_head)){  // if the list has data to pop (means not empty)
                printf("Enter position (1 ~ list_length, list_length is now: %d)\n>>", list_length(list_head));
                scanf("%d", &target_pos);
                data = remove_list(list_head, target_pos);
                printf("The removed data is: %d", data);
            }
            else printf("The list is empty, nothing to remove");
            break;

            case 5:
            print_all(list_head);
            break;

            case 6:
            if(!empty(list_head)){  // if the list no yet empty
                clear(list_head);
                print_all(list_head);
            }
            else printf("The list is empty, nothing to clear");
            break;

            case 7:
            printf("The list's length is: %d", list_length(list_head));
            break;

            case 10:
            commands();
            break;

            case 0:
            print_all(list_head);
            if(!empty(list_head)){  // if the list no yet empty
                clear(list_head);
            }
            printf("\nExit");
            exit(1);
            break;

            default:
            printf("Invalid command!!");
            break;
        }
        printf("\n");
    }


    return 0;
}