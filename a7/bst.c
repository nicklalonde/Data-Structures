/*
 * Nicholas Lalonde
 * 169030544
 * March 6th, 2024
 * lalo0544@mylaurier.ca
 * BST.C
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


BSTNODE *new_node(RECORD data);
BSTNODE *extract_smallest_node(BSTNODE **rootp);

BSTNODE *new_node(RECORD data){
    BSTNODE *node = (TNODE*)malloc(sizeof(TNODE));
    if(node != NULL){
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        return;
    }
}


BSTNODE *bst_search(BSTNODE *root, char *key) {

BSTNODE *p = NULL;
while(root){
    if(root.data == key){
        p = root;
        break;
    }
    else if (root->data > key){
        root = root->left;
    }
    else if (root->data < key){
        root = root->right;
    }
}
return p;

}


void bst_insert(BSTNODE **rootp, RECORD data) {
// your code
    if(*rootp == NULL){
        *rootp = new_node(data);
    }
}

void bst_delete(BSTNODE **rootp, char *key) {
// your code
}



BSTNODE *new_node(RECORD data) {
    BSTNODE *np = (BSTNODE *) malloc(sizeof(BSTNODE));
    if (np) {
        memcpy(np, &data, sizeof(BSTNODE));
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

BSTNODE *extract_smallest_node(BSTNODE **rootp) {
    BSTNODE *p = *rootp, *parent = NULL;
    if (p) {
        while (p->left) {
            parent = p;
            p = p->left;
        }

        if (parent == NULL)
            *rootp = p->right;
        else
            parent->left = p->right;

        p->left = NULL;
        p->right = NULL;
    }

    return p;
}

void clean_bst(BSTNODE **rootp) {
    BSTNODE *root = *rootp;
    if (root) {
        if (root->left)
            clean_bst(&root->left);
        if (root->right)
            clean_bst(&root->right);
        free(root);
    }
    *rootp = NULL;
}