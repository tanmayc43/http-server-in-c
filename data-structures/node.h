struct Node{
    void *data; //void pointer, needs casting
    struct Node *next;
    struct Node *prev;
};

struct Node node_constructor(void *data, u_long size);

void node_destructor(struct Node *node);
