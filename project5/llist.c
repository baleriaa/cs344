#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

int main (int argc, char *argv[]) {
    struct node *head = NULL;
    // for (int i = 1; i < argc; i++) {
    //     if (strcmp(argv[i], "ih") == 0) {
    //         printf("%s", argv[i]);
    //         // llist_insert_head();
    //     } 
    //     else if (strcmp(argv[i], "it") == 0) {
    //         // llist_insert_tail();
    //         printf("%s", argv[i]);
    //     } 
    //     else if (strcmp(argv[i], "dh") == 0) {
    //         // llist_delete_head();
    //         printf("%s", argv[i]);
    //     }
    //     else if (strcmp(argv[i], "f") == 0) {
    //         // llist_free();
    //         printf("%s", argv[i]);
    //     }
    //     else if (strcmp(argv[i], "p") == 0) {
    //         // llist_print();
    //         printf("%s", argv[i]);
    //     }
    //     else {
    //         printf("Invalid command. Please choose either: ih, it, dh, f, or p.");
    //         exit(1);
    //     }
    // }
    struct node *test_node = node_alloc(45);
    struct node *test_node2 = node_alloc(47);
    llist_insert_head(&test_node, test_node2);
    llist_print(NULL);
    // node_free(test_node);
    // llist_print(test_node);

}

struct node *node_alloc(int value) {
    struct node *node = malloc(sizeof(struct node));
    node->value = value;
    node->next = NULL;
    return node;
}

void node_free(struct node *n) {
    free(n);
}

void llist_print(struct node *head) {
    struct node *current = head;
    if (head == NULL) {
        printf("[empty]");
    }
    else {
        while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
        }
    }  
}

void llist_insert_head(struct node **head, struct node *n) {
    n->next = *head;
    *head = n;
}


struct node *llist_delete_head(struct node **head);
void llist_insert_tail(struct node **head, struct node *n);

void llist_free(struct node **head);




