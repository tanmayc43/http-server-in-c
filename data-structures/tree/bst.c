#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node * bst_node_constructor(void *data, unsigned long size);
void bst_node_destructor(struct Node  *node);
struct Node * bst_iterator(struct bst *tree, struct Node *curr_node, void *data, int *direction);
void bst_recursive_destructor(struct Node *node);

void * bst_search(struct bst *tree, void *data);
void bst_insert(struct bst *tree, void *data, unsigned long size);

struct bst bst_constructor(int(*compare)(void *data_one, void *data_two)){
    struct bst tree;
    tree.head = NULL;
    tree.compare = compare;
    tree.search = bst_search;
    tree.insert = bst_insert;

    return tree;
}

void bst_destructor(struct bst tree){
    bst_recursive_destructor(tree.head);
}

struct Node * bst_node_constructor(void *data, unsigned long size){
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));
    *node = node_constructor(data, size);
    return node;
}

void bst_node_destructor(struct Node *node){
    node_destructor(node);
}

struct Node * bst_iterator(struct bst *tree, struct Node *curr_node, void *data, int *direction){

    if(tree->compare(curr_node->data, data)==1){
        if(curr_node->next) return bst_iterator(tree, curr_node->next, data, direction);

        else{
            *direction=1;
            return curr_node;
        }
    }
    else if(tree->compare(curr_node->data, data)==-1){
        if(curr_node->prev) return bst_iterator(tree, curr_node->prev, data, direction);
        else{
            *direction=-1;
            return curr_node;
        }
    }
    else{
        *direction=0;
        return curr_node;
    }
}


void bst_recursive_destructor(struct Node *node){
    if(node->prev) bst_recursive_destructor(node->prev);
    if(node->next) bst_recursive_destructor(node->next);
    bst_node_destructor(node);
}


void * bst_search(struct bst *tree, void *data){
    int direction=0;
    struct Node *curr_node = bst_iterator(tree, tree->head, data, &direction);

    if(direction==0) return curr_node->data;
    else return NULL;
}

void bst_insert(struct bst *tree, void *data, unsigned long size){
    if(!tree->head) tree->head = bst_node_constructor(data, size);
    else{
        int direction=0;
        struct Node *curr_node = bst_iterator(tree, tree->head, data, &direction);
        if(direction==1) curr_node->next = bst_node_constructor(data, size);
        else if(direction==-1) curr_node->prev = bst_node_constructor(data,size); //not adding duplicate nodes
    }
}

int bst_compare_str(void *data_one, void *data_two){
    int comparison = strcmp(data_one, data_two);
    if(comparison > 0) return 1;
    else if(comparison < 0) return -1;
    return 0;
}