#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void dict_recursive_destructor(struct Node *node);

void dict_insert(struct Dictionary *dict, void *key, unsigned long key_size, void *value, unsigned long value_size);
void * dict_search(struct Dictionary *dict, void *key, unsigned long key_size);

struct Dictionary dict_constructor(int (*compare)(void *key_one, void *key_two)){
    struct Dictionary dictionary;
    dictionary.tree = bst_constructor(compare);
    dictionary.keys = ll_constructor();
    dictionary.insert = dict_insert;
    dictionary.search = dict_search;
    return dictionary;
}

void dict_destructor(struct Dictionary *dictionary){
    ll_destructor(&dictionary->keys);
    dict_recursive_destructor(dictionary->tree.head);
}

void dict_recursive_destructor(struct Node *node){
    if(node->prev) dict_recursive_destructor(node->prev);
    if(node->next) dict_recursive_destructor(node->next);

    entry_destructor((struct Entry *)node->data); // casting node to entry
    free(node->data);
    free(node);
}


void * dict_search(struct Dictionary *dictionary, void *key, unsigned long key_size){
    int dummy_value = 0;
    struct Entry searchable = entry_constructor(key, key_size, &dummy_value, sizeof(dummy_value));
    void * result = dictionary->tree.search(&dictionary->tree, &searchable);
    if(result) return ((struct Entry *)result)->value;
    else return NULL;
}

void dict_insert(struct Dictionary *dictionary, void *key, unsigned long key_size, void *value, unsigned long value_size){
    struct Entry entry = entry_constructor(key, key_size, value, value_size);
    dictionary->tree.insert(&dictionary->tree, &entry, sizeof(entry));
    dictionary->keys.insert(&dictionary->keys, dictionary->keys.length, key, key_size);
}



int compare_keys(void *entry_one, void *entry_two){
    if (strcmp((char *)(((struct Entry *)entry_one)->key), (char *)(((struct Entry *)entry_two)->key)) > 0) return 1;
    else if (strcmp((char *)(((struct Entry *)entry_one)->key), (char *)(((struct Entry *)entry_two)->key)) < 0) return -1;
    return 0;
}