// Learning from:
// https://stackoverflow.com/questions/16522341/pseudo-generics-in-c

#ifndef __STACK_GEN_H__
#define __STACK_GEN_H__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define create_stack_struct(T, T_NAME)     \
typedef struct stack_##T_NAME {     \
    T item;                         \
    struct stack_##T_NAME *next;    \
} Stack_##T_NAME;

#define stack_push(T, T_NAME)                                   \
static void stack_push_##T_NAME(Stack_##T_NAME **top, T item) { \
    Stack_##T_NAME *new_node = malloc(sizeof(Stack_##T_NAME));  \
    new_node->item = item;                                      \
    if (*top == NULL) {                                         \
        new_node->next = NULL;                                  \
        *top = new_node;                                        \
    } else {                                                    \
        new_node->next = *top;                                  \
        *top = new_node;                                        \
    }                                                           \
}

#define stack_pop(T, T_NAME)                \
static T stack_pop_##T_NAME(Stack_##T_NAME **top) {\
    if (*top == NULL) {                     \
        fprintf(stderr, "Stack is empty");  \
        return (T)0;                        \
    }                                       \
    Stack_##T_NAME *poped_node = *top;      \
    *top = (*top)->next;                    \
    T poped_item = poped_node->item;        \
    free(poped_node);                       \
    return poped_item;                      \
}

#define stack_empty(T, T_NAME)                          \
static bool stack_empty_##T_NAME(Stack_##T_NAME *top) { \
    return (top == NULL);                               \
}


#define STACK_CREATION(T, T_NAME)   \
create_stack_struct(T, T_NAME);     \
stack_push(T, T_NAME);              \
stack_pop(T, T_NAME);               \
stack_empty(T, T_NAME);

#define stack_foreach(current, top)     \
            for (current = top; current != NULL; current = current->next)

#endif  // __STACK_GEN_H__
