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
            block->in_use = 1;  // mark it in use
            return PTR_OFFSET(block, PADDED_SIZE(sizeof(struct block)));    // return a pointer to the user data
        }
        block = block->next;
    }
    return NULL;    // if no block is found, return NULL
}

int main(void) {
    void *p;

    print_data();
    p = myalloc(16);
    print_data();
    p = myalloc(16);
    printf("%p\n", p);
}

