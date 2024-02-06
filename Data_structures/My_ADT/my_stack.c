#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_stack.h"


void test_func(void){
    printf("Test result: OK");
}


void stack_push(stack **top, void *data){
    stack *new_node = malloc(sizeof(stack));
    new_node->data = data;
    new_node->type_info = "None";

    if(*top == NULL){
        *top = new_node;
        new_node->next_node = NULL;
        return;
    }

    new_node->next_node = *top;
    *top = new_node;
}


void *stack_pop(stack **top){
    /* This function doesn't check if the stack is empty or not */

    stack *poped_node = *top;
    void *poped_data = (*top)->data;

    *top = (*top)->next_node;
    
    free(poped_node);
    
    return poped_data;
}


void stack_push_with_type_info(stack **top, void *data, char *info){
    /* If needed, add a type infomation to the head of the stack to specified the data type.
    Or, if the stack stores many data types, add info to each of them */

    stack_push(top, data);
    (*top)->type_info = info;
}


stack stack_pop_with_type_info(stack **top){
    stack *poped_node = *top;
    stack poped_data_and_type_info = {
        .data = (*top)->data, 
        .type_info = (*top)->type_info
    };

    *top = (*top)->next_node;
    free(poped_node);

    // printf("loc: %p\n", &poped_data_and_type_info);

    return poped_data_and_type_info;
}


int stack_length(stack *top){
	int length = 0;
	stack *cur = top;
	
	while (cur != NULL){
		length++;
		cur = cur->next_node;
	}
	
	return length;
}


int stack_empty(stack *top){
    /* 0: not empty, 1: empty */
    if (top == NULL) return 1;
    return 0;
}


void stack_print_all(stack *top){
    /* Not recommand use this function, it's better to print them all by yourself*/
    /* Only if the type_info is the same as it's data type name, like int or char, (special: string) */
    /* This function dosen't contan all the built-in data types */
    stack *cur = top;

    printf("Top-->[");
    while (cur != NULL){
        char *type = cur->type_info;
        
        if (strcmp(type, "int") == 0){
            printf("%d", *(int *)cur->data);
        }
        else if (strcmp(type, "float") == 0){
            printf("%f", *(float *)cur->data);
        }
        else if (strcmp(type, "double") == 0){
            printf("%lf ", *(double *)cur->data);
        }

        else if (strcmp(type, "unsigned int") == 0){
            printf("%u", *(unsigned int *)cur->data);
        }

        else if (strcmp(type, "char") == 0){
            printf("%c", *(char *)cur->data);
        }
        else if(strcmp(type, "string") == 0){
            printf("\"%s\"", (char *)cur->data);
        }
        else{
            printf("UNKOWN TYPE");
        }


        if (cur->next_node == NULL){
            printf("]\n");
        }
        else{
            printf(", ");
        }
        cur = cur->next_node;
    }
}


void stack_clear(stack **top){
    while (!stack_empty(*top)){
        stack_pop(top);
    }
}