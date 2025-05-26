#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"

struct Queue{
    struct Linked_list list;

    void(*push)(struct Queue *queue, void *data, unsigned long data_size);
    void(*pop)(struct Queue *queue);
    void * (*peek)(struct Queue *queue);
};

struct Queue queue_constructor(void);
void queue_destructor(struct Queue *queue);


#endif //QUEUE_H