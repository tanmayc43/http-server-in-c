#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

struct Node *ll_node_constructor(void *data, unsigned long size);
void ll_node_destructor(struct Node *node);

struct Node *ll_iterator(struct Linked_list *ll, int index);
void ll_insert(struct Linked_list *ll, int index, void *data, unsigned long size);
void ll_remove(struct Linked_list *ll, int index);
void * ll_finder(struct Linked_list *ll, int index);
void ll_sort(struct Linked_list *ll, int(*compare)(void *x, void *y));
short ll_search(struct Linked_list *ll, void *query, int(*compare)(void *x, void *y));


struct Linked_list ll_constructor(){
    struct Linked_list list;
    list.head = NULL;
    list.length = 0;

    list.insert= ll_insert;
    list.remove= ll_remove;
    list.finder = ll_finder;
    list.search = ll_search;
    list.sort = ll_sort;

    return list;
};

void ll_destructor(struct Linked_list *ll){
    for(int i=0;i<ll->length;i++) ll->remove(ll, 0);
}

struct Node * ll_node_constructor(void *data, unsigned long size){
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    *new_node = node_constructor(data, size);
    return new_node;
}

void ll_node_destructor(struct Node *node){
    node_destructor(node);
}

struct Node * ll_iterator(struct Linked_list *ll, int index){
    if(index < 0 || index >= ll->length) return NULL;
    struct Node *curr_node = ll->head;
    for(int i=0;i<index;i++) curr_node = curr_node->next;
    return curr_node;
}


void ll_insert(struct Linked_list *ll, int index, void *data, unsigned long size){
    struct Node *new_node = ll_node_constructor(data, size);
    if(index == 0){
        new_node->next = ll->head;
        ll->head = new_node;
    }
    else{
        struct Node *curr_node = ll_iterator(ll, index-1);
        new_node->next = curr_node->next;
        curr_node->next = new_node;
    }
    ll->length += 1;
}

void ll_remove(struct Linked_list *ll, int index){
    if(index == 0){
        struct Node *node = ll->head;
        if(node){
            ll->head = node->next;
            ll_node_destructor(node);
        }
    }
    else{
        struct Node *curr_node = ll_iterator(ll, index-1);
        struct Node *node = curr_node->next;
        curr_node->next = node->next;
        ll_node_destructor(node);
    }
    ll->length -= 1;
}

void * ll_finder(struct Linked_list *ll, int index){
    struct Node *curr_node = ll_iterator(ll, index);
    if(curr_node) return curr_node->data;
    else return NULL;
}


void ll_sort(struct Linked_list *ll, int (*compare)(void *x, void *y)){
    for(struct Node *i = ll->finder(ll, 0);i; i=i->next){
        for (struct Node *n = i->next;n; n=n->next){
            if(compare(i->data, n->data) > 0){
                void *temp = n->data;
                n->data = i->data;
                i->data = temp;
            }
        }
    }
}

short ll_search(struct Linked_list *ll, void *query, int (*compare)(void *x, void *y)){
    int mid = ll->length/2, lo = 0, hi = ll->length;
    while(hi > lo){
        void *data = ll->finder(ll, mid);
        if(compare(data, query) == 1){
            hi = mid;
            if(mid != (lo+mid)/2) mid = (lo+mid)/2;
            else break;
        }
        else if(compare(data, query) == -1){
            lo = mid;
            if(mid != (hi+mid)/2) mid = (hi+mid)/2;
            else break;
        
        }
        else return 1;
    }
    return 0;
}