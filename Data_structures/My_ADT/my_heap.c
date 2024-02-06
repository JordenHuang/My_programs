#include <stdio.h>
#include <stdlib.h>

// min_heap

struct heap_node{
    int num;
    struct heap_node *parent;
    struct heap_node *left_node;
    struct heap_node *right_node;
};

typedef struct heap_node heap;


void heapify(heap *heap_head, heap *last_child){
    while(last_child->num < last_child->parent->num){
            if(last_child->parent->left_node == last_child){
                last_child = last_child->parent;
                last_child->parent = last_child->parent->parent;
                last_child->parent = last_child;


                 
            }
        
    }
}


void insert(heap *heap_head, heap *last_child, int data){
    heap *new_node = malloc(sizeof(heap));
    new_node->left_node=NULL;
    new_node->right_node=NULL;
    new_node->num = data;

    if(last_child->left_node==NULL){
        last_child->left_node = new_node;
        new_node->parent = last_child;
    }
    else{
        last_child->right_node = new_node;
        new_node->parent = last_child;
    }
    last_child = new_node;

    heapify(heap_head, last_child);
}


int main(){
    heap *heap_head;
    heap_head->parent = NULL;
    heap_head->left_node = NULL;
    heap_head->right_node = NULL;
}