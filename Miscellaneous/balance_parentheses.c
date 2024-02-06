#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct stackNode{
    char data;
    struct stackNode *nextPtr;
};

typedef struct stackNode stack;

void stack_push(stack **top, char data_to_push){
    stack *new_node = malloc(sizeof(stack));
    new_node->data = data_to_push;

    if(*top == NULL){
        *top = new_node;
        new_node->nextPtr = NULL;
        return;
    }

    new_node->nextPtr = *top;
    *top = new_node;
}


char stack_pop(stack **top){
    stack *poped_node = *top;
    char poped_data = (*top)->data;
    *top = (*top)->nextPtr;
    free(poped_node);

    return poped_data;
}


int empty(stack *top){
    if(top == NULL) return 1;
    else return 0;
}


void printf_all(stack *top){
    stack *temp=top;
    stack *sec_stack = NULL;

    while(! empty(temp)){
        stack_push(&sec_stack, temp->data);
        temp = temp->nextPtr;
    }
    while(! empty(sec_stack)){
        printf("%c ", stack_pop(&sec_stack));
    }
    printf("\n");
}


int main(){
    stack *top=NULL;
    char parenthese;
    bool not_balanced = false;

    printf("Enter parentheses: ");
    do{
        scanf("%c", &parenthese);
        if(parenthese == '\n') break;

        if(empty(top)){
            stack_push(&top, parenthese);
            continue;
        }
        if(parenthese == '(' || parenthese == '[' || parenthese == '{'){
            stack_push(&top, parenthese);
        }
        else{
            switch(top->data){
                case '(':
                if(parenthese == ')'){
                    stack_pop(&top);
                }
                else not_balanced = true;
                break;

                case '[':
                if(parenthese == ']'){
                    stack_pop(&top);
                }
                else not_balanced = true;
                break;

                case '{':
                if(parenthese == '}'){
                    stack_pop(&top);
                }
                else not_balanced = true;
                break;
            }
        }

        if(not_balanced == true) break;

        // printf_all(top);

    } while(1);

    if(empty(top)) printf("Balanced!!");
    else printf("NOT balanced");
    
    return 0;
}