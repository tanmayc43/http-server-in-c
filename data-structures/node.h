#ifndef NODE_H
#define NODE_H

struct Node{
    void *data; //void pointer, needs casting
    struct Node *next;
    struct Node *prev;
};

struct Node node_constructor(void *data, unsigned long size);

void node_destructor(struct Node *node);

#endif // NODE_H