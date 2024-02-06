#include <stdio.h>
#include <stdlib.h>

// unbalanced binary search tree

struct tree_node{
    int num;
    struct tree_node *left_node;
    struct tree_node *right_node;
};

typedef struct tree_node tree;

tree *root = NULL;


tree *insert(tree *root, int data){
    char direction='l';
    tree *new_node = malloc(sizeof(tree));
    tree *pre, *current=root;

    new_node->num = data;
    new_node->left_node = NULL;
    new_node->right_node = NULL;

    // if the tree is empty
    if(root == NULL){
        printf("a1\n");
        return new_node;
    }
    // else insert to the correct position
    while(current != NULL){
        pre = current;
        if(data < current->num){
            current = current->left_node;
            direction = 'l';
            printf("a2\n");
        }
        else{
            current = current->right_node;
            direction = 'r';
            printf("a3\n");
        }
    }
    if(direction == 'l') pre->left_node = new_node;
    else pre->right_node = new_node;

    return root;
}


int find_and_delete_smallest(){
    tree *pre, *current = root;
    int smallest_data;

    if(root->left_node == NULL && root->right_node == NULL){
        smallest_data = root->num;
        // free(root);
        root = NULL;
        printf("c1");
        return smallest_data;
    }

    else if(root->left_node == NULL){
        smallest_data = root->num;
        root = root->right_node;
        free(current);
        printf("c2");
        return smallest_data;
    }

    while(current->left_node != NULL){
        pre = current;
        current = current->left_node;
    }
    pre->left_node = current->right_node;
    smallest_data = current->num;
    free(current);
    printf("c3");
    return smallest_data;
}


int main(){
    
    int s;

    root = insert(root, 1);
    root = insert(root, -1);
    root = insert(root, 10);
    root = insert(root, 100);
    // root = insert(root, -1000);
    // root = insert(root, 10000);

    s = find_and_delete_smallest(root);
    printf("s is: %d, done\n", s);

    while(root != NULL){
        s = find_and_delete_smallest(root);
        printf("s is: %d\n", s);
    }
    free(root);
    
    return 0;
}