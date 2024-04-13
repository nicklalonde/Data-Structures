/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <math.h>
#include "queue_stack.h"
#include "bst.h"
#include "myrecord_bst.h"

void add_record(BSTDS *tree, RECORD record) {
// your code
    if(bst_search(tree->root, record.name) == NULL){
        bst_insert(&tree->root, record);
        int count = tree->count;
        float score = record.score;
        float mean = tree->mean;
        float stddev = tree->stddev;
        tree->count += 1;
        tree->mean = ((float)1/((float)count+(float)1))*((float)count*(float)mean + score);
        tree->stddev = sqrtf(((float)1/((float)count+(float)1))*((float)count*(stddev*stddev + mean*mean)+(score*score))-(tree->mean*tree->mean));
    }
}

void remove_record(BSTDS *tree, char *key) {

    BSTNODE *p = bst_search(tree->root, key);
    if(p!=NULL){
        float score = p->data.score;
        bst_delete(&(tree->root), key);
        int count = tree->count;
        float mean = tree->mean;
        float stddev = tree->stddev;
        tree->count = count - 1;

        if (tree->count <= 1){
            tree->stddev = 0.0;
            if(tree->count == 0){
                tree->mean  =0.0;
            }
            else{
                tree->mean = (count * mean - score);
            }
        }
        else {
            tree->mean = (count * mean - score) / (count - 1);
            float newstddev =  sqrtf(((float)1/(float)(tree->count))*((float)count*(stddev*stddev + mean*mean) - (score*score))-(tree->mean*tree->mean));
            tree->stddev = newstddev;
            
        }
    }
}

void clean_bstds(BSTDS *ds) {
  clean_bst(&ds->root);
  ds->count = 0;
  ds->mean = 0;
  ds->stddev = 0;
}