#include "../node.h"


struct bst{
    struct Node *head;

    int(*compare)(void *data_one, void *data_two);
    void *(*search)(struct bst *tree, void *data);
    void *(*insert)(struct bst *tree, void *data, u_long size);

};

struct bst bst_constructor(int(*compare)(void *data_one, void *data_two));
void  bst_destructor(struct bst tree);


void bst_compare_int(void *data_one, void *data_two);
void bst_compare_char(void *data_one, void *data_two);
void bst_compare_float(void *data_one, void *data_two);
void bst_compare_str(void *data_one, void *data_two);