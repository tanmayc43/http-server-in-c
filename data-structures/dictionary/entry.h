struct Entry{
    void *key;
    void *value;
};

struct Entry entry_constructor(void *key, u_long key_size, void *value, u_long value_size);
void entry_destructor(struct Entry *entry);