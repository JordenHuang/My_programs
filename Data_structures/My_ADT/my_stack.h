
#ifndef _MY_STACK_H_
#define _MY_STACK_H_

/*/ TODO: check this
 * Not store the data in the stack, but store the address of the data
 *
 * 
/*/

struct stack_node {
    void *data;
    char *type_info;
    struct stack_node *next_node;
};

typedef struct stack_node stack;


void test_func(void);

// stack *stack_new(stack *top);

void stack_push(stack **top, void *data);

// return (void *)
void *stack_pop(stack **top);

void stack_push_with_type_info(stack **top, void *data, char *info);

stack stack_pop_with_type_info(stack **top);


int stack_length(stack *top);

int stack_empty(stack *top);

void stack_print_all(stack *top);

void stack_clear(stack **top);

#endif