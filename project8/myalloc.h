struct block {
    struct block *next;
    int size;     // Bytes
    int in_use;   // Boolean
};


void *myalloc(int size);
void myfree(void *p);
void split(struct block *current_node, int requested_size);
