#include "linked_list.h"
#include <stdio.h>

struct Node *ll_node_constructor(void *data, u_long size);
void ll_node_destructor(struct Node *node);

struct Node *ll_iterator(struct Linked_list *ll, int index);
void ll_insert(struct Linked_list *ll, int index, void *data, u_long size);
void ll_remove(struct Linked_list *ll, int index);
void * ll_finder(struct Linked_list *ll, int index);
void ll_sort(struct Linked_list *ll, int(*compare)(void *x, void *y));
void ll_search(struct Linked_list *ll, void *query, int(*compare)(void *x, void *y));


struct Linked_list ll_constructor(){
    struct Linked_list list;
    list.head = NULL;
    list.length = 0;

    list.insert= ll_insert;
    list.remove= ll_remove;
    list.finder = finder;
    list.search = ll_search;
    list.sort = ll_sort;

    return list;
}

void Linked_list ll_destructor(struct Linked_list *ll){
    for(int i=0;i<ll->length;i++) ll->ll_remove(ll, 0);
}

