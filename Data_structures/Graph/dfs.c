#include <stdio.h>
#include <stdlib.h>

#include "graph_adjacency_list.c"

#define size 5+1

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


void dfs(node **adjacency_list, int i, int *time)
{
    visited[i].visited = 1;
    node *cur = adjacency_list[i];
    int t=cur->vertex;
    while(cur != NULL){
        if(!visited[t].visited){
            visited[t].predecessor = i;
            visited[t].first = ++(*time);
            // printf("time: %d\n", *time);
            dfs(adjacency_list, t, time);
            visited[t].finish = ++(*time);
            // printf("time: %d\n", *time);
        }
        
        cur = cur->next;
        if(cur != NULL) t = cur->vertex;
    }
}


int main()
{
    int i;
    node **adjacency_list = create_adjacency_list(size);
    // add_adjacency_list_node(adjacency_list, 0, 1, 0, 0);
    // add_adjacency_list_node(adjacency_list, 0, 2, 0, 0);
    add_adjacency_list_node(adjacency_list, 0, 5, 0, 0);
    // add_adjacency_list_node(adjacency_list, 1, 2, 0, 0);
    add_adjacency_list_node(adjacency_list, 1, 5, 0, 0);
    add_adjacency_list_node(adjacency_list, 2, 3, 0, 0);
    add_adjacency_list_node(adjacency_list, 2, 4, 0, 0);
    add_adjacency_list_node(adjacency_list, 3, 4, 0, 0);
    add_adjacency_list_node(adjacency_list, 3, 5, 0, 0);
    add_adjacency_list_node(adjacency_list, 4, 5, 0, 0);
    show_adjacency_list(adjacency_list, size);

    initialize_arrays();

    // dfs
    int time = 0;
    for(i=0; i<size; i++){
        if(!visited[i].visited){
            visited[i].predecessor = -1;
            visited[i].first = time;
            dfs(adjacency_list, i, &time);
            visited[i].finish = ++time;
        }
    }

    // print out the infomations
    // all vertex visited ?
    // for(i=0; i<size; i++){
    //     printf("%2d ", visited[i].visited);
    // }
    // printf("\n");

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