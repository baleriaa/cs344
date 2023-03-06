#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
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

void myfree(void *pointer){
    struct block *block = PTR_OFFSET(pointer, -PADDED_SIZE(sizeof(struct block)));  
    block->in_use = 0; 
    coalesce(block);
}
void split(struct block *current_node, int requested_size) {
    if (current_node->in_use) {
        exit(1);
    }
    int required_size = PADDED_SIZE(requested_size) + PADDED_SIZE(sizeof(struct block));
    int available_space = current_node->size;
    if (required_size <= available_space) {
        struct block *new_block = PTR_OFFSET(current_node, required_size);
        new_block->next = current_node->next;
        new_block->size = available_space - required_size;
        new_block->in_use = 0;
        current_node->next = new_block;
        current_node->size = PADDED_SIZE(requested_size);
    }
}

void coalesce(struct block *head_node) {
    struct block *current_node = head_node;
    while (current_node->next != NULL) {
        if (current_node->in_use == 0 && current_node->next->in_use == 0) {
            current_node->size += current_node->next->size + PADDED_SIZE(sizeof(struct block));
            current_node->next = current_node->next->next;
        } 
        else current_node = current_node->next;
    }
}


int main(void) {
void *p, *q, *r, *s;

p = myalloc(10); print_data();
q = myalloc(20); print_data();
r = myalloc(30); print_data();
s = myalloc(40); print_data();

myfree(q); print_data();
myfree(p); print_data();
myfree(s); print_data();
myfree(r); print_data();
}

