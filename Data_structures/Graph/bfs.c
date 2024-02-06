#include <stdio.h>
#include <stdlib.h>

#include "graph_adjacency_list.c"

#define size 8+1

// ================== Queue =========================
typedef struct queue{
    node *vertex;
    struct queue *next;
}queue;

queue *enqueue(queue **head, node *vertex)
{
    queue *new_node = malloc(sizeof(queue *));
    new_node->vertex = vertex;
    new_node->next = NULL;

    if(*head == NULL){
        *head = new_node;
        return *head;
    }

    queue *cur = *head;
    while(cur->next != NULL){
        cur = cur->next;
    }
    cur->next = new_node;
}

node *dequque(queue **head)
{
    node *item = (*head)->vertex;
    queue *old_head = *head;
    *head = (*head)->next;
    free(old_head);
    return item;
}

int queue_empty(queue *head)
{
    if(head == NULL) return 1;
    else return 0;
}


// ==================== bfs ============================

typedef struct visited_struct{
    int predecessor;
    int visited;
    int first;
    int finish;
}visited_struct;

visited_struct visited[size];

void initialize_arrays()
{
    int i;
    for(i=0; i<size; i++){
        visited[i].predecessor = -1;
        visited[i].visited = 0;
        visited[i].first = 0;
        visited[i].finish = 0;
    }
}


void bfs(node **adjacency_list)
{
    queue *head = NULL;
    node *cur;
    int i, j, predecessor, time = -1;
    for(i=0; i<size; i++){
        if(visited[i].visited == 0){
            visited[i].visited = 1;
            visited[i].first = ++time;
            visited[i].finish = ++time;
            visited[i].predecessor = -1;

            cur = adjacency_list[i];
            predecessor = i;
            while(cur != NULL){
                if(!visited[cur->vertex].visited){
                    enqueue(&head, cur);
                    visited[cur->vertex].visited = 1;
                    visited[cur->vertex].first = ++time;
                    visited[cur->vertex].predecessor = predecessor;
                }
                cur = cur->next;
            }

            // bfs
            while(!queue_empty(head)){
                cur = dequque(&head);
                visited[cur->vertex].finish = ++time;
                predecessor = cur->vertex;

                cur = adjacency_list[cur->vertex];
                while(cur != NULL){
                    if(!visited[cur->vertex].visited){
                        visited[cur->vertex].visited = 1;
                        visited[cur->vertex].first = ++time;
                        visited[cur->vertex].predecessor = predecessor;
                        enqueue(&head, cur);
                    }
                    cur = cur->next;
                }
            }
        }
    }
}


int main()
{
    int i;
    node **adjacency_list = create_adjacency_list(size);
    // sample 1
    ///*
    // add_adjacency_list_node(adjacency_list, 0, 1, 0, 0);//
    // add_adjacency_list_node(adjacency_list, 0, 2, 0, 0);//
    add_adjacency_list_node(adjacency_list, 0, 5, 0, 0);
    // add_adjacency_list_node(adjacency_list, 1, 2, 0, 0);//
    add_adjacency_list_node(adjacency_list, 1, 5, 0, 0);
    add_adjacency_list_node(adjacency_list, 2, 3, 0, 0);
    add_adjacency_list_node(adjacency_list, 2, 4, 0, 0);
    add_adjacency_list_node(adjacency_list, 3, 4, 0, 0);
    add_adjacency_list_node(adjacency_list, 3, 5, 0, 0);
    add_adjacency_list_node(adjacency_list, 4, 5, 0, 0);
    //*/

    // sample 2
    /*
    add_adjacency_list_node(adjacency_list, 0, 1, 0, 0);
    add_adjacency_list_node(adjacency_list, 0, 2, 0, 0);
    add_adjacency_list_node(adjacency_list, 0, 3, 0, 0);
    add_adjacency_list_node(adjacency_list, 1, 4, 0, 0);
    add_adjacency_list_node(adjacency_list, 2, 4, 0, 0);
    add_adjacency_list_node(adjacency_list, 2, 5, 0, 0);
    add_adjacency_list_node(adjacency_list, 2, 6, 0, 0);
    add_adjacency_list_node(adjacency_list, 2, 7, 0, 0);
    add_adjacency_list_node(adjacency_list, 3, 7, 0, 0);
    add_adjacency_list_node(adjacency_list, 4, 5, 0, 0);
    add_adjacency_list_node(adjacency_list, 5, 8, 0, 0);
    add_adjacency_list_node(adjacency_list, 6, 7, 0, 0);
    add_adjacency_list_node(adjacency_list, 6, 8, 0, 0);
    */
   
    show_adjacency_list(adjacency_list, size);

    initialize_arrays();

    // bfs
    
    // for(i=0; i<size; i++){
    //     if(!visited[i].visited){printf("?");
    //         visited[i].predecessor = -1;
    //         visited[i].visited = 1;
    //         visited[i].first = time;
    //         // enqueue(&head, adjacency_list[i]);
    //         bfs(adjacency_list, &head, i, &time);
    //         visited[i].finish = ++time;
    //     }
    // }

    bfs(adjacency_list);

    // print out the infomations
    // all vertex visited ?
    for(i=0; i<size; i++){
        printf("%2d ", visited[i].visited);
    }
    printf("\n");

    // the predessors
    for(i=0; i<size; i++){
        printf("%2d ", visited[i].predecessor);
    }
    printf("\n");

    // first visit time of the vertex
    for(i=0; i<size; i++){
        printf("%2d ", visited[i].first);
    }
    printf("\n");

    // finish time of the vertex
    for(i=0; i<size; i++){
        printf("%2d ", visited[i].finish);
    }
    printf("\n");

    free_adjacency_list(&adjacency_list, size);

    return 0;
}