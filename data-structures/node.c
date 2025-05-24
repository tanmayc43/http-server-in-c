#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node node_constructor(void *data, u_long size){
    if(size<1){
        perror("Invalid data size for node. \n");
        exit(1);
    }

    struct Node node;
    node.data = malloc(size);
    memcpy(node.data, data, size);
    node.next = NULL;
    node.prev = NULL;
    return node;
}

void node_destructor(struct Node *node){
    free(node->data);
    free(node)
}