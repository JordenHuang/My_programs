#include <stdio.h>
#include <stdlib.h>


int **create_adjacency_matrix(int size)
{
    int **m = malloc(sizeof(int *) * size);
    int i, j;
    for(i=0; i<size; i++){
        m[i] = malloc(sizeof(int *) * size);

        // initialize to all zero
        for(j=0; j<size; j++){
            m[i][j] = 0;
        }
    }
    return m;
}

void free_adjacency_matrix(int ***m, int size)
{
    int i;
    for(i=0; i<size; i++) free((*m)[i]);

    free(*m);
    *m = NULL;
}

void show_adjacency_matrix(int **m, int size)
{
    int i, j;
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}



void delete_vertex(int **m, int v, int size)
{
    int i;
    for(i=0; i<size; i++){
        m[v][i] = 0;
        m[i][v] = 0;
    }
}

void add_edge(int **m, int from, int to, int direct_g)
{
    m[from][to] = 1;
    if(!direct_g){    
        m[to][from] = 1;
    }
}

void delete_edge(int **m, int from, int to, int direct_g)
{
    m[from][to] = 0;
    if(!direct_g){
        m[to][from] = 0;
    }
}



#if(0)
int main()
{
    int **m = create_adjacency_matrix(5);
    int i, j;
    int size = 5;

    show_adjacency_matrix(m, size);

    add_edge(m, 0, 1, 0);
    add_edge(m, 0, 3, 0);
    add_edge(m, 2, 3, 0);
    show_adjacency_matrix(m, size);
    
    delete_edge(m, 0, 1, 0);
    show_adjacency_matrix(m, size);

    delete_vertex(m, 3, size);
    show_adjacency_matrix(m, size);

    free_adjacency_matrix(&m, size);
    return 0;
}
#endif