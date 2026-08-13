// Learn from:
// https://stackoverflow.com/questions/16522341/pseudo-generics-in-c

#ifndef __GSTACK_H__
#define __GSTACK_H__

#ifdef T

#include <stdio.h>
#include <stdlib.h>

#define TOKEN_PASTE(a, b) a##b
#define STACK(T) TOKEN_PASTE(Stack_, T)

typedef struct STACK(T) {
    T item;
    struct STACK(T) *next;
} STACK(T);

#define STACK_PUSH(T) TOKEN_PASTE(stack_push_, T)
void STACK_PUSH(T) (STACK(T) **top, T item) {
    STACK(T) *new_node = malloc(sizeof(STACK(T)));
    new_node->item = item;

    if (*top == NULL) {
        new_node->next = NULL; 
        *top = new_node;
    } else {
        new_node->next = *top;
        *top = new_node;
    }
}

#define STACK_POP(T) TOKEN_PASTE(stack_pop_, T)
T STACK_POP(T) (STACK(T) **top) {
    if (*top == NULL) {
        fprintf(stderr, "Stack is empty");
        return (T)0;
    }
    STACK(T) *poped_node = *top;
    *top = (*top)->next;
    T poped_item = poped_node->item;
    free(poped_node);
    return poped_item;
}

#define stack_foreach(current, top)     \
            for (current = top; current != NULL; current = current->next)


#endif  // T

#endif  // __GSTACK_H__
