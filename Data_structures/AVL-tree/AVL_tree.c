#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int data;
    struct tree *left;
    struct tree *right;
    int height_from_buttom;
    int balance_factor;
}tree;


/*
TODO:

[x]predecessor
[x]secessor

[x]max
[x]node height from buttom
[x]balance factor

[x]left rotate
[x]right rotate

[x]binary search tree insertion

[x]tree_free_all

main functions:
    [x]avl tree insert
    [x]avl tree delete
    [x]inorder traveral
*/

void my_debug_print(char *tag){
    printf("%s\n", tag);
}



void binary_search_tree_insertion(tree **root, int data){
    tree *new_node = (tree *)malloc(sizeof(tree));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    if(*root == NULL){
        *root = new_node;
    }
    else{
        char last_move = 'x';
        tree *cur = *root;
        while(1){
            if(data <= cur->data){
                last_move = 'l';
                if(cur->left != NULL){
                    cur = cur->left;
                }
                else break;
            }
            else if(data > cur->data){
                last_move = 'r';
                if(cur->right != NULL){
                    cur = cur->right;
                }
                else break;
            }
        }
        // concate the link
        if(last_move == 'l')cur->left = new_node;
        else cur->right = new_node;
    }
}

void tree_inorder(tree *node){
    if(node == NULL) return;

    tree_inorder(node->left);

    printf("%d ", node->data);

    tree_inorder(node->right);
}

void tree_preorder(tree *node){
    if(node == NULL) return;

    printf("%d ", node->data);

    tree_preorder(node->left);

    tree_preorder(node->right);
}

void tree_free_all(tree *node){
    // traverse in postorder and free the node, the first node passed in is not freed
    if(node == NULL) return;
    
    tree_free_all(node->left);
    tree_free_all(node->right);
    free(node);
}

void tree_free_all_v2(tree **node){
    // traverse in postorder and free the node, the first node passed in is also freed
    if(*node == NULL) return;
    
    tree_free_all_v2(&((*node)->left));
    tree_free_all_v2(&((*node)->right));
    free(*node);
}


tree *predecessor(tree *node){
    /* find node's predecessor */
    if(node->left == NULL){
        return NULL;
    }
    else{
        tree *cur = node->left;
        while(cur->right != NULL){
            cur = cur->right;
        }
        return cur;
    }
}

tree *successor(tree *node){
    /* find node's secessor */
    if(node->right == NULL){
        return NULL;
    }
    else{
        tree *cur = node->right;
        while(cur->left != NULL){
            cur = cur->left;
        }
        return cur;
    }
}


int max(int left, int right){
    return (left >= right) ? left : right;
}

tree *calc_node_height_and_balance_factor(tree *node){
    int left, right;
    if(node->left == NULL){
        left = -1;
    }
    else{
        left = node->left->height_from_buttom;
    }

    if(node->right == NULL){
        right = -1;
    }
    else{
        right = node->right->height_from_buttom;
    }
    
    node->height_from_buttom = max(left, right) + 1;
    node->balance_factor = left - right;

    return node;
}


void tree_left_rotate(tree **node){
    /*
        Do left rotate on the node
        let A be the node, and B be the A's right child
        
        Set A's right child = B's left child
        then, set B's left child = A
    */

   // rotate (relink the link)
   tree *right_child = (*node)->right;
    (*node)->right = right_child->left;
    right_child->left = *node;

    // update the height and balance factor
    *node = calc_node_height_and_balance_factor(*node);
    right_child = calc_node_height_and_balance_factor(right_child);


    *node = right_child;
}

void tree_right_rotate(tree **node){
    /*
        Do right rotate on the node
        let A be the node, and B be the A's left child

        Set A's left child = B's right child
        then, set B's right child = A
    */

   // rotate (relink the link)
   tree *left_child = (*node)->left;
   (*node)->left = left_child->right;
   left_child->right = *node;

    // update the height and balance factor
    *node = calc_node_height_and_balance_factor(*node);
    left_child = calc_node_height_and_balance_factor(left_child);
   
   *node = left_child;
}


tree *avl_tree_update_balance(tree *node){
    // check if the node is balanced or not, if it's not balanced, then rotate it
    // BF > 1 means the left subtree is more havier
    if(node->balance_factor > 1){
        // my_debug_print("test 4.1");
        // if the left subtree's left subtree is heavier, then it's Left Left case
        if(node->left->balance_factor == 1){
            tree_right_rotate(&node);
            // my_debug_print("test 4.1.1");
        }
        // else, it's Left Right case
        else{
            tree_left_rotate(&(node->left));
            tree_right_rotate(&node);
            // my_debug_print("test 4.1.2");
        }
        return node;
    }
    //BF < -1 means the right subtree is more havier
    else if(node->balance_factor < -1){
        // my_debug_print("test 4.2");
        // if the right subtree's right subtree is heavier, then it's Right Right case
        if(node->right->balance_factor == -1){
            tree_left_rotate(&node);
            // my_debug_print("test 4.2.1");
        }
        // else, it's Right Left case
        else{
            tree_right_rotate(&(node->right));
            tree_left_rotate(&node);
            // my_debug_print("test 4.2.2");
        }
        return node;
    }

    return node;
}


tree *avl_tree_insertion(tree *node, int data){
    /* It's a recursive AVL tree insertion function*/

// my_debug_print("test 0");
    // base case
    if(node == NULL){
        tree *new_node = (tree *)malloc(sizeof(tree));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->height_from_buttom = 0;
        return new_node;
    }

    // my_debug_print("test 1");

    // traverse to the correct position for insert
    if(data <= node->data) node->left = avl_tree_insertion(node->left, data);
    else if(data > node->data) node->right = avl_tree_insertion(node->right, data);

    // my_debug_print("test 2");

    // update every node's height and BF that's being traversed
    node = calc_node_height_and_balance_factor(node);

    // my_debug_print("test 3");

    // update tree's balance
    node = avl_tree_update_balance(node);

    return node;
}


tree *avl_tree_deletion(tree *node, int target_data){
    // traverse to the correct position
    if(node == NULL){
        fprintf(stdout, "Data not found in the tree. No data to be delete\n");
        return NULL;
    }
    else if(target_data < node->data) node->left = avl_tree_deletion(node->left, target_data);
    else if(target_data > node->data) node->right = avl_tree_deletion(node->right, target_data);
    
    // found the target data, do binary search tree deletion
    else{
        // If the node has no child (means leaf node)
        if(node->left == NULL && node->right == NULL){
            free(node);
            return NULL;
        }
        
        // Or if the node has one child
        // if the node's child is on the left
        else if(node->right == NULL){
            tree *left = node->left;
            free(node);
            return left;
        }

        // if the node's child is on the right
        else if(node->left == NULL){
            tree *right = node->right;
            free(node);
            return right;
        }
        
        // Or if the node has two children
        else{
            /* find the node with largest data (call B) in the node's left subtree
                swap B's data with the node
                then call the deletion to delete B
            */
            tree *prede = predecessor(node);
            
            int temp_data = node->data;
            node->data = prede->data;
            prede->data = temp_data;
            node->left = avl_tree_deletion(node->left, prede->data);
        }
    }

    // update every node's height and BF that's being traversed
    node = calc_node_height_and_balance_factor(node);

    // update tree's balance
    node = avl_tree_update_balance(node);
    
    return node;
}


int main(){
    tree *root = NULL;
    tree *binary_root = NULL;
    int data[] = {5, 3, 2, 6, 9, 8, 4, 1, 7, 10};
    int i = 0;

    // to check if the inorder of the avl tree is the same as the binary search tree
/*  
    for(i=0; i<10; i++){
        root = avl_tree_insertion(root, data[i]);
        // my_debug_print("second");
        binary_search_tree_insertion(&binary_root, data[i]);
        // my_debug_print("third");
    }

    printf("The AVL tree inorder traversal: \n");
    tree_inorder(root);

    printf("\nThe binary search tree inorder traversal: \n");
    tree_inorder(binary_root);

    printf("\n\nThe AVL tree preorder traversal: \n");
    tree_preorder(root);

    printf("\nThe binary search tree preorder traversal: \n");
    tree_preorder(binary_root);


    tree_free_all_v2(&root);
    tree_free_all_v2(&binary_root);
*/
    for(i=0; i<10; i++){
        root = avl_tree_insertion(root, data[i]);
        // my_debug_print("second");
        // binary_search_tree_insertion(&binary_root, data[i]);
        // my_debug_print("third");
    }

    printf("The AVL tree inorder traversal: \n");
    tree_inorder(root);

    printf("The AVL tree inorder traversal: \n");
    root = avl_tree_deletion(root, 6);
    tree_inorder(root);


    tree_free_all_v2(&root);

    return 0;
}