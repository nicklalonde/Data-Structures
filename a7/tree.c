#include "tree.h"
#include "queue_stack.h"

/* Compute and return the TPROPS value of a tree.
 * @param root - pointer to the root of a tree
 * @return - number of nodes and height in TPROPS type.
 */
TPROPS tree_property(TNODE *root){
    TPROPS r = {0};
    if (root == NULL)
        return r;
    else{
        TPROPS lp = tree_property(root->left);
        TPROPS rp = tree_property(root->right);
        r.order = lp.order + rp.order;
        r.height = (lp.height > rp.height) ? lp.height + 1 : rp.height + 1;
        return r;
    }
}

/* Display the node data of the tree in pre-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */
void preorder(TNODE *root){
    if(root == NULL)
        return;
    printf("%c ", root->data);
    preorder(root->left);
    preorder(root->right);
    return;
}

/* Display the node data of the tree in in-order and format "%c".
 *
 *  @param root - pointer to the root of a tree
 */
void inorder(TNODE *root){
    if (root == NULL){
        return;
    }

    inorder(root->left);
    printf("%c ", root->data);
    inorder(root->right);
    return;
}

/* Display the node data of the tree in post-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */
void postorder(TNODE *root){
    if(root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%c ", root->data);
}

/* Display the node data of the tree in breadth-first-order and format "%c ".
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 */
void bforder(TNODE *root){

    if (root == NULL) return;
    QUEUE q = {0};
    TNODE *p = NULL;
    enqueue(&q, root);
    while (q.front) {
        p = dequeue(&q);
        if(p){
            printf("%c ", p->data);
            enqueue(&q, p->left);
            enqueue(&q, p->right);
        }
    }

}

/* Search by key using breadth-first-search algorithm
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */
TNODE *bfs(TNODE *root, char key){
    TNODE *r = NULL;
    if(root){
        QUEUE queue = {0};
        enqueue(&queue, root);
        while(queue.front){
            TNODE *tnp = (TNODE*)dequeue(&queue);
            //1. check match, if matched set r=p, break
            if(tnp->data == key){
                r = tnp;
                break;
            }
            //2. enqueue the left child
            if(tnp->left) enqueue(&queue, tnp->left);
            //3. enqueue the right child
            if(tnp->right) enqueue(&queue, tnp->right);

        }
        clean_queue(&queue);
    }
    return r;

}


/* Search by key using depth-first-search algorithm.
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */
TNODE *dfs(TNODE *root, char key){
    TNODE *r = NULL;
    if(root){
        STACK stack = {0};
        push(&stack, root);
        while(stack.top){
            TNODE *p = pop(&stack);
            if(p->data == key){
                r = p;
                break;
            }
            if(p->left) push(&stack, p->left);
            if(p->right) push(&stack, p->right);
        }
        clean_stack(&stack);
    }
    return r;
}


// The following functions are given in a7 help.

/* Create a TNODE node and sets the data to value and returns the pointer.
 * Use malloc()
 */
TNODE *new_node(char val) {
    TNODE *np = (TNODE *) malloc(sizeof(TNODE));
    if (np != NULL) {
        np->data = val;
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

void clean_tree(TNODE **rootp) {
    TNODE *p = *rootp;
    if (p) {
        if (p->left)
            clean_tree(&p->left);
        if (p->right)
            clean_tree(&p->right);
        free(p);
    }
    *rootp = NULL;
}

void insert_tree(TNODE **rootp, char val) {
    if (*rootp == NULL) {
        *rootp = new_node(val);
    } else {
        QUEUE queue = { 0 };
        TNODE *p;
        enqueue(&queue, *rootp);
        while (queue.front) {
            p = dequeue(&queue);
            if (p->left == NULL) {
                p->left = new_node(val);
                break;
            } else {
                enqueue(&queue, p->left);
            }

            if (p->right == NULL) {
                p->right = new_node(val);
                break;
            } else {
                enqueue(&queue, p->right);
            }
        }
    }
}