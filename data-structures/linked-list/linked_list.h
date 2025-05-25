#include "../node.h"

struct Linked_list{
    struct Node *head;
    int length;

    void(*insert)(struct Linked_list *ll, int index, void *data, unsigned long size);
    void(*remove)(struct Linked_list *ll, int index);
    void * (*finder)(struct Linked_list *ll, int index);
    void(*sort)(struct Linked_list *ll, int(*compare)(void *x, void *y));
    short (*search)(struct Linked_list *ll, void *query, int(*compare)(void *x, void *y));

};

struct Linked_list ll_constructor(void);
void ll_destructor(struct Linked_list *ll);