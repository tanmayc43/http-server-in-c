#include "queue.h"

void push(struct Queue *queue, void *data, unsigned long data_size);
void * peek(struct Queue *queue);
void pop(struct Queue *queue);

struct Queue queue_constructor(){
    struct Queue queue;

    queue.list = ll_constructor();
    queue.push = push;
    queue.pop= pop;
    queue.peek = peek;

    return queue;
}

void queue_destructor(struct Queue *queue){
    ll_destructor(queue->list);
}

void push(struct Queue *queue, void *data, unsigned long data_size){
    queue->list.insert(&queue->list, queue->list.length, data, data_size);
}

void pop(struct Queue *queue){
    queue->list.remove(&queue->list, 0);
}

void * peek(struct Queue *queue){
    void * data = Queue->list.finder(&queue->list, 0);
    return data;
}