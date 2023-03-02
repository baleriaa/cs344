#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include "myalloc.h"

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))
#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))

struct block *head = NULL;

void print_data(void)
{
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }
        b = b->next;
    }
    printf("\n");
}

void *myalloc(int size) {
    if (head == NULL) {
    head = mmap(NULL, 1024, PROT_READ|PROT_WRITE,
                MAP_ANON|MAP_PRIVATE, -1, 0);
    head->next = NULL;
    head->size = 1024 - PADDED_SIZE(sizeof(struct block));
    head->in_use = 0;
    } 
    struct block *block = head;
    while (block != NULL) {         // walk the linked list
        if (block->in_use == 0 && block->size >= size) {    // if the block is not in use and is big enough
            split(block, size);     
            block->in_use = 1;  // mark it in use
            return PTR_OFFSET(block, PADDED_SIZE(sizeof(struct block)));    // return a pointer to the user data
        }
        block = block->next;
    }
    return NULL;    // if no block is found, return NULL
}

// void myfree(void *pointer){NULL}
void split(struct block *current_node, int requested_size) {
    int head_size = PADDED_SIZE(sizeof(struct block));
    if (current_node->size > requested_size + head_size) {  // if current_node big enough to split
        struct block *new_block = PTR_OFFSET(current_node, head_size + requested_size);     // Add a new struct block with the remaining unused space
        new_block->next = current_node->next;      
        new_block->size = current_node->size - requested_size;  // set the size of the new block to the remaining size
        new_block->in_use = 1;  // mark the new block as in use
        current_node->next = new_block;   //
        current_node->size = requested_size; 
    }
}

int main(void) {
    void *p;

    print_data();
    p = myalloc(16);
    print_data();
    p = myalloc(16);
    printf("%p\n", p);
}

