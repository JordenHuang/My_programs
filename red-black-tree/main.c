// TODO: Clean up erase related functions
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

enum RBTreeColor {
    RBT_BLACK = 0,
    RBT_RED   = 1,
};

typedef struct RBTreeNode {
    int data;
    enum RBTreeColor color;
    struct RBTreeNode *parent;
    struct RBTreeNode *left;
    struct RBTreeNode *right;
} RBTreeNode;

typedef struct RBTree {
    RBTreeNode *root;
} RBTree;

#define RBTREE_ROOT (RBTree) {NULL, }

void rbt_insert(RBTree *tree, int data);
void rbt_erase(RBTree *tree, RBTreeNode *node); /* User needs to find the node first, then erase it by this function, and free the node manually */
RBTreeNode *rbt_search(RBTree tree, int data);
void rbt_destory(RBTree *tree);
void rbt_inorder(const RBTree tree /*, void (*cb)(RBTreeNode *node) */);
/* In-order */
RBTreeNode *rbt_first(const RBTree *tree); // TODO:
RBTreeNode *rbt_last(const RBTree *tree); // TODO:
RBTreeNode *rbt_next(RBTreeNode *node);
RBTreeNode *rbt_prev(RBTreeNode *node);
/* Post-order */
RBTreeNode *rbt_next_postorder(RBTreeNode *node);
RBTreeNode *rbt_first_postorder(const RBTree tree);

static RBTreeNode *rbt_create_node(int data)
{
    RBTreeNode *node = malloc(sizeof(RBTreeNode));
    node->data = data;
    node->color = RBT_RED;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void rbt_destory(RBTree *tree)
{
    RBTreeNode *node = rbt_first_postorder(*tree);

    while (node != NULL) {
        RBTreeNode *next = rbt_next_postorder(node);
        free(node);
        node = next;
    }

    tree->root = NULL;
}

static void rbt_left_rotate(RBTree *tree, RBTreeNode *node)
{
    /*
    *     .            .
    *    / \          / \
    *   n   .   --> tmp  .
    *    \          /
    *    tmp       n
    */
    if (!node)
        return;

    RBTreeNode *tmp = node->right;
    node->right = tmp->left;

    if (tmp->left) /* Turn tmp's left subtree into node's right subtree */
        tmp->left->parent = node;

    tmp->parent = node->parent; /* Link node's parent to tmp */

    if (node->parent == NULL)
        tree->root = tmp;
    else if (node == node->parent->left)
        node->parent->left = tmp;
    else
        node->parent->right = tmp;

    tmp->left = node; /* Put node on tmp's left */
    node->parent = tmp;
}

static void rbt_right_rotate(RBTree *tree, RBTreeNode *node)
{
    /*
    *       .          .
    *      / \        / \
    *     n   . --> tmp  .
    *    /            \
    *  tmp             n
    */
    if (!node)
        return;

    RBTreeNode *tmp = node->left;
    node->left = tmp->right;

    if (tmp->right) /* Turn tmp's right subtree into node's left subtree */
        tmp->right->parent = node;

    tmp->parent = node->parent; /* Link node's parent to tmp */

    if (node->parent == NULL)
        tree->root = tmp;
    else if (node == node->parent->left)
        node->parent->left = tmp;
    else
        node->parent->right = tmp;

    tmp->right = node; /* Put node on tmp's right */
    node->parent = tmp;
}

static void rbt_insert_fixup(RBTree *tree, RBTreeNode *node)
{
    RBTreeNode *parent = node->parent, *gparent, *tmp;

    while (true) {
        if (!parent) {
            node->color = RBT_BLACK;
            tree->root->color = RBT_BLACK;
            break;
        }

        if(parent->color == RBT_BLACK)
            break;

        gparent = parent->parent;

        if (parent == gparent->left) { /* parent == gparent->left */
            tmp = gparent->right;
            if (tmp && tmp->color == RBT_RED) {
                /*
                 * Case 1: node's uncle is red
                 *
                 * Color filp, and propagate up on gparent
                 */
                parent->color  = RBT_BLACK;
                tmp->color     = RBT_BLACK;
                gparent->color = RBT_RED;
                node = gparent;
                parent = gparent->parent;
                continue;
            }

            if (node == parent->right) {
              /*
               * Case 2 - node's uncle is black and node is the parent's right
               * child (left rotate at parent). (black nodes are uppercase and
               * red nodes will be lowercase.)
               *     G            G
               *    / \          / \
               *   P   U   -->  n   U
               *    \          /
               *     n        p
               */
                node = parent;
                rbt_left_rotate(tree, node);
            }

            /*
             * Case 3 - node's uncle is black and node is the parent's left
             * child (right rotate at gparent).
             *
             *        G           P
             *       / \         / \
             *      p   U  -->  n   g
             *     /                 \
             *    n                   U
             */
            node->parent->color         = RBT_BLACK;
            node->parent->parent->color = RBT_RED;
            rbt_right_rotate(tree, node->parent->parent);
            break;
        } else {
            tmp = gparent->left;
            if (tmp && tmp->color == RBT_RED) {
                /*
                 * Case 1: node's uncle is red
                 *
                 * Color filp, and propagate up on gparent
                 */
                parent->color  = RBT_BLACK;
                tmp->color     = RBT_BLACK;
                gparent->color = RBT_RED;
                node = gparent;
                parent = gparent->parent;
                continue;
            }

            if (node == parent->left) {
              /*
               * Case 2 - right rotate at parent
               *     G            G
               *    / \          / \
               *   U   P   -->  U   n
               *      /              \
               *     n                p
               */
                node = parent;
                rbt_right_rotate(tree, node);
            }

            /*
             * Case 3 - node's uncle is black and node is the parent's right
             * child (left rotate at gparent).
             *
             *        G           P
             *       / \         / \
             *      U   p  -->  g   n
             *           \     /
             *            n   U
             */
            node->parent->color         = RBT_BLACK;
            node->parent->parent->color = RBT_RED;
            rbt_left_rotate(tree, node->parent->parent);
            break;
        }
    }
}

void rbt_insert(RBTree *tree, int data)
{
    RBTreeNode *node = rbt_create_node(data); /* New node to be inserted */

    /* Binary tree inseration */
    RBTreeNode *prev = NULL, *cur = tree->root;
    while (cur != NULL) {
        prev = cur;
        if (node->data < cur->data) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    node->parent = prev;

    if (prev == NULL) {
        tree->root = node;
    } else if (node->data < prev->data) {
        prev->left = node;
    } else {
        prev->right = node;
    }

    rbt_insert_fixup(tree, node); /* Fixup to follow the properties */
}

/*
 * Transparent
 *
 * Set a to be b
 */
static void rbt_transplant(RBTree *tree, RBTreeNode *a, RBTreeNode *b)
{
    RBTreeNode *p = a->parent;
    if (!p)
        tree->root = b;
    else if (a == p->left)
        p->left = b;
    else
        p->right = b;
    if (b)
        b->parent = p;
}

static inline int rbt_is_black(RBTreeNode *node) {
    return (node == NULL || node->color == RBT_BLACK);
}

static inline int rbt_is_red(RBTreeNode *node) {
    return (node != NULL && node->color == RBT_RED);
}

static void rbt_erase_fixup(RBTree *tree, RBTreeNode *node, RBTreeNode *parent)
{
    RBTreeNode *w;

    while (node != tree->root && rbt_is_black(node)) {
        if (node == parent->left) {
            w = parent->right;

            /* Case 1: Sibling is RED */
            if (rbt_is_red(w)) {
                w->color = RBT_BLACK;
                parent->color = RBT_RED;
                rbt_left_rotate(tree, parent);
                w = parent->right;
            }

            /* Case 2: Sibling is BLACK, both children are BLACK (or NULL) */
            // if (w && (rbt_is_black(w->left) && rbt_is_black(w->right))) {
            if ((rbt_is_black(w->left) && rbt_is_black(w->right))) {
                // if (w)
                    w->color = RBT_RED;
                node = parent;
                parent = node->parent;
            } 
            else {
                /* Case 3: Sibling is BLACK, left child is RED, right child is
                 * BLACK
                 */
                // if (w && rbt_is_black(w->right)) {
                if (rbt_is_black(w->right)) {
                    // if (w->left)
                        w->left->color = RBT_BLACK;
                    // if (w)
                        w->color = RBT_RED;
                    rbt_right_rotate(tree, w);
                    w = parent->right;
                }

                /* Case 4: Sibling is BLACK, right child is RED */
                // if (w)
                    w->color = parent->color;
                parent->color = RBT_BLACK;
                // if (w->right)
                    w->right->color = RBT_BLACK;

                rbt_left_rotate(tree, parent);
                node = tree->root;
            }
        } else {
            w = parent->left;

            /* Case 1: Sibling is RED */
            if (rbt_is_red(w)) {
                w->color = RBT_BLACK;
                parent->color = RBT_RED;
                rbt_right_rotate(tree, parent);
                w = parent->left;
            }

            /* Case 2: Sibling is BLACK, both children are BLACK (or NULL) */
            // if (w && (rbt_is_black(w->left) && rbt_is_black(w->right))) {
            if ((rbt_is_black(w->left) && rbt_is_black(w->right))) {
                // if (w)
                    w->color = RBT_RED;
                node = parent;
                parent = node->parent;
            } 
            else {
                /* Case 3: Sibling is BLACK, left child is RED, right child is
                 * BLACK
                 */
                // if (w && rbt_is_black(w->left)) {
                if (rbt_is_black(w->left)) {
                    // if (w->right)
                        w->right->color = RBT_BLACK;
                    // if (w)
                        w->color = RBT_RED;
                    rbt_left_rotate(tree, w);
                    w = parent->left;
                }

                /* Case 4: Sibling is BLACK, right child is RED */
                // if (w)
                    w->color = parent->color;
                parent->color = RBT_BLACK;
                // if (w->left)
                    w->left->color = RBT_BLACK;

                rbt_right_rotate(tree, parent);
                node = tree->root;
            }
        }
    }

    if (node) {
        node->color = RBT_BLACK;
    }
}

void rbt_erase(RBTree *tree, RBTreeNode *node)
{
    RBTreeNode *child;
    RBTreeNode *parent;
    enum RBTreeColor original_color;

    if (!node)
        return;

    original_color = node->color;

    if (!node->left) {
        /* Node only has right child */
        child = node->right;
        parent = node->parent;
        rbt_transplant(tree, node, child);
    } else if (!node->right) {
        /* Node only has left child */
        child = node->left;
        parent = node->parent;
        rbt_transplant(tree, node, child);
    } else {
        /* Node has both left and right child */

        /*
         * Find predecessor
         *
         * The rightmost node of node's left subtree
         * This node is used to replace the node to be removed
         * */
        RBTreeNode *predecessor = node->left;
        while (predecessor->right)
            predecessor = predecessor->right;

        original_color = predecessor->color;
        child = predecessor->left;

        if (predecessor->parent == node) {
            /*
             * Case 2: node's successor(in my case, predecessor) is its left child
             *
             *    (n)          (s)
             *    / \          / \
             *  (s) (x)  ->  (c) (x)
             *    \
             *    (c)
             */
            parent = predecessor;
        } else {
            /*
             * Case 3: node's successor(in my case, predecessor) is rightmost under
             * node's left child subtree
             *    (n)          (s)
             *    / \          / \
             *  (y) (x)  ->  (y) (x)
             *    \            \
             *    (p)          (p)
             *      \            \
             *      (s)          (c)
             *      /
             *    (c)
             */
            parent = predecessor->parent;
            rbt_transplant(tree, predecessor, predecessor->left);

            /* Set left child and its parent */
            predecessor->left = node->left;
            predecessor->left->parent = predecessor;
        }

        rbt_transplant(tree, node, predecessor);

        /* Set right child and it's parent */
        predecessor->right = node->right;
        predecessor->right->parent = predecessor;
        predecessor->color = node->color;
    }

    if (original_color == RBT_BLACK) {
        rbt_erase_fixup(tree, child, parent);
    }
}

RBTreeNode *rbt_search(RBTree tree, int data)
{
    RBTreeNode *cur = tree.root;
    while (cur != NULL) {
        if (cur->data < data)
            cur = cur->right;
        else if (cur->data > data)
            cur = cur->left;
        else
            break;
    }

    return cur;
}

void rbt_inorder(RBTree tree /*, void (*cb)(RBTreeNode *node) */)
{
    RBTreeNode *node = tree.root;
    while (node->left)
        node = node->left;

    while (node != NULL) {
        printf("%d, ", node->data);
        node = rbt_next(node);
    }
}

RBTreeNode *rbt_next(RBTreeNode *node)
{
    if (node == NULL) return NULL;

    /* Case 1: node has right child */
    if (node->right) {
        /* Find the leftmost node of current node's right child */
        node = node->right;
        while (node->left)
            node = node->left;
        return node;
    }

    /* Case 2: node has no right child. Go up the tree */
    RBTreeNode *parent = node->parent;
    while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

RBTreeNode *rbt_prev(RBTreeNode *node)
{
    if (node == NULL) return NULL;

    /* Case 1: node has left child */
    if (node->left) {
        /* Find the rightmost node of current node's left child */
        node = node->left;
        while (node->right)
            node = node->right;
        return node;
    }

    /* Case 2: node has no left child. Go up the tree */
    RBTreeNode *parent = node->parent;
    while (parent && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

static RBTreeNode *rbt_left_deepest_node(RBTreeNode *node)
{
    while (1) {
        if (node->left)
            node = node->left;
        else if (node->right)
            node = node->right;
        else
            return node;
    }
}

RBTreeNode *rbt_next_postorder(RBTreeNode *node)
{	
    const RBTreeNode *parent;
    if (!node)
        return NULL;
    parent = node->parent;

    /* If we're sitting on node, we've already seen our children */
    if (parent && node == parent->left && parent->right) {
        /* If we are the parent's left node, go to the parent's right
         * node then all the way down to the left */
        return rbt_left_deepest_node(parent->right);
    } else
    /* Otherwise we are the parent's right node, and the parent
         * should be next */
    return (RBTreeNode *)parent;
}

RBTreeNode *rbt_first_postorder(const RBTree tree)
{
	if (!tree.root)
		return NULL;

	return rbt_left_deepest_node(tree.root);
}

int main(void)
{
    // int data[] = {5, 3, 2, 6, 9, 8, 4, 1, 7, 10};
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    RBTree tree = RBTREE_ROOT;

    for(int i = 0; i < 10; i++){
        rbt_insert(&tree, data[i]);
    }

    printf("The red-black tree inorder traversal: \n");
    rbt_inorder(tree);

    int n;
    RBTreeNode *node;

    // printf("\nSearch: ");
    // scanf("%d", &n);
    // while (n != -1) {
    //     node = rbt_search(tree, n);
    //     if (node)
    //         printf("\nResult: %d", node->data);
    //     else
    //         printf("\nNot found");
    //     printf("\nSearch: ");
    //     scanf("%d", &n);
    // }

    printf("\nErase: ");
    scanf("%d", &n);
    while (n != -1) {
        node = rbt_search(tree, n);
        if (node) {
            rbt_erase(&tree, node);
            free(node);
        } else
            printf("\nNot found");
        printf("\nErase: ");
        scanf("%d", &n);
    }

    // printf("The red-black tree inorder traversal: \n");
    // rbt_inorder(tree);

    printf("\nSearch: ");
    scanf("%d", &n);
    while (n != -1) {
        node = rbt_search(tree, n);
        if (node) {
            printf("\nResult: %d", node->data);
            printf("\nColor: %s", (node->color == RBT_BLACK) ? "Black" : "Red");
        } else
            printf("\nNot found");
        printf("\nSearch: ");
        scanf("%d", &n);
    }

    rbt_destory(&tree);
    return 0;
}
