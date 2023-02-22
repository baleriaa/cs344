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
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}





// If this is the first call, mmap() to get some space.
// At the same time, build a linked-list node inside the new space indicating its size and "in-use" status.
// Walk the linked list in a loop and look for the first node that is:
// Not in-use
// Big enough to hold the requested amount (plus padding)
// If the block is found:
// Mark it in-use.
// Return a pointer to the user data just after the linked list node (plus padding)).
// If no such block is found:
// Return NULL