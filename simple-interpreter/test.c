/*
#include <stdio.h>
#include <stdlib.h>

#define node_append(head, node)     \
do {                                \
    list_t *list = (list_t *)(head);\
    list->next = (list_t *)(node);  \
} while(0)                          \

typedef struct list_t {
    struct list_t *next;
} list_t;

typedef struct node {
    list_t list_head;
    int data;
} node_t;

void node_new(node_t **node, int data)
{
    node_t *new_node = malloc(sizeof(node_t));
    new_node->list_head.next = NULL;
    new_node->data = data;
    *node = new_node;
}

void node_print(node_t *node_head)
{
    list_t *list = (list_t *)node_head;
    printf("Data: ");
    while (list) {
        printf("%d, ", ((node_t*)list)->data);
        list = list->next;
    }
    printf("end\n");
}

void node_free_all(node_t *node_head)
{
    list_t *prev = (list_t *)node_head;
    list_t *list = ((list_t *)node_head)->next;
    while (list) {
        prev = list;
        list = list->next;
        free(prev);
    }
}

int main(void)
{
    printf("Program begin\n");

    node_t *node;
    node_new(&node, 0);

    node_t *node2;
    node_new(&node2, 1);
    node_append(node, node2);

    node_t *node3;
    node_new(&node3, 2);
    node_append(node2, node3);

    node_print(node);

    // free(node);
    // free(node2);
    node_free_all(node);
    printf("Program exit\n");
    return 0;
}
*/
#include <stdio.h>
#include <stddef.h>

#define theoffsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define my_offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)1000)->MEMBER)

struct test {
    int a;
    int b;
    int c;
};

int main()
{
    printf("sizeof(int): %ld\n", sizeof(int));

    printf("--- theoffsetof -------------\n");
    printf("-------- a: %ld\n", theoffsetof(struct test, a));
    printf("-------- b: %ld\n", theoffsetof(struct test, b));
    printf("-------- c: %ld\n", theoffsetof(struct test, c));

    printf("--- my_offsetof -------------\n");
    printf("-------- a: %ld\n", my_offsetof(struct test, a));
    printf("-------- b: %ld\n", my_offsetof(struct test, b));
    printf("-------- c: %ld\n", my_offsetof(struct test, c));

    printf("--- offsetof -------------\n");
    printf("-------- a: %ld\n", offsetof(struct test, a));
    printf("-------- b: %ld\n", offsetof(struct test, b));
    printf("-------- c: %ld\n", offsetof(struct test, c));

    int a;
    typeof(a) b;

    return 0;
}
