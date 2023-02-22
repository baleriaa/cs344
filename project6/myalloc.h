struct block {
    struct block *next;
    int size;     // Bytes
    int in_use;   // Boolean
}


void *myalloc(int size);
void myfree(void *p);
