#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "entry.h"
#include "../tree/bst.h"
#include "../linked-list/linked_list.h"

struct Dictionary{
    struct bst tree;
    struct Linked_list keys;
    void(*insert)(struct Dictionary *dict, void *key, unsigned long key_size, void *value, unsigned long value_size);
    void * (*search)(struct Dictionary *dict, void *key, unsigned long key_size);
};


struct Dictionary dict_constructor(int(*compare)(void *x, void *y));
void dict_destructor(struct Dictionary *dict);

int compare_keys(void *x, void *y);

#endif //DICTIONARY_H