#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int vertex;
    int weight;
    struct node *next;
}node;


node **create_adjacency_list(int number_of_vertex)
{
    int i;
    // FIXME: should +1 in number_of_vertex in case for vertex naming starting with 1, rather than 0 ?
    node **list_head = malloc(sizeof(node*) * (number_of_vertex));
    for(i=0; i<number_of_vertex; i++){
        list_head[i] = NULL;
    }
    return list_head;
}

void free_adjacency_list(node ***list_head, int number_of_vertex)
{
    int i;
    node *cur, *pre;
    for(i=0; i<number_of_vertex; i++){
        cur = (*list_head)[i];
        while(cur != NULL){
            pre = cur;
            cur = cur->next;
            free(pre);
        }
    }
    free(*list_head);
    *list_head = NULL;
}

void show_adjacency_list(node **list_head, int number_of_vertex)
{
    int i;
    node *cur;
    for(i=0; i<number_of_vertex; i++){
        cur = list_head[i];
        printf("Adjacency list of vertex %d:\nhead -> ", i);
        while(cur != NULL){
            printf("%d(%c) %d ", cur->vertex, cur->vertex+65, cur->weight);
            if(cur->next != NULL) printf("-> ");

            cur = cur->next;
        }
        printf("\n");
    }
}

void add_adjacency_list_node(node **list_head, int from, int to, int weight, int direct_g)
{
    node *new_node = malloc(sizeof(node));
    new_node->vertex = to;
    new_node->weight = weight;
    new_node->next = NULL;

    if(list_head[from] == NULL){
        list_head[from] = new_node;
    }
    else{
        node *cur = list_head[from];
        while(cur->next != NULL) cur = cur->next;
        cur->next = new_node;
    }
    // if it's an undirected graph
    if(!direct_g){
        new_node = malloc(sizeof(node));
        new_node->vertex = from;
        new_node->weight = weight;
        new_node->next = NULL;

        if(list_head[to] == NULL){
            list_head[to] = new_node;
        }
        else{
            node *cur = list_head[to];
            while(cur->next != NULL) cur = cur->next;
            cur->next = new_node;
        }
    }
}


#if(0)
int main()
{
    int number_of_vertex = 4;
    node **adjacency_list = create_adjacency_list(number_of_vertex);

    add_adjacency_list_node(adjacency_list, 0, 1, 0, 0);
    add_adjacency_list_node(adjacency_list, 0, 2, 0, 0);
    add_adjacency_list_node(adjacency_list, 0, 3, 0, 0);

    add_adjacency_list_node(adjacency_list, 1, 2, 0, 0);
    add_adjacency_list_node(adjacency_list, 1, 3, 0, 0);
    
    add_adjacency_list_node(adjacency_list, 2, 3, 0, 0);


    show_adjacency_list(adjacency_list, number_of_vertex);

    free_adjacency_list(&adjacency_list,  number_of_vertex);
    return 0;
}
#endif