#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

int main (int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "ih") == 0) {
            print("%s", argv[i]);
            // llist_insert_head();
        } 
        else if (strcmp(argv[i], "it") == 0) {
            // llist_insert_tail();
            print("%s", argv[i]);
        } 
        else if (strcmp(argv[i], "dh") == 0) {
            // llist_delete_head();
            print("%s", argv[i]);
        }
        else if (strcmp(argv[i], "f") == 0) {
            // llist_free();
            print("%s", argv[i]);
        }
        else if (strcmp(argv[i], "p") == 0) {
            // llist_print();
            print("%s", argv[i]);
        }
        else {
            print("Invalid command. Please choose either: ih, it, dh, f, or p.");
        }
    }
}

struct node *node_alloc(int value) {
    struct node *node = malloc(sizeof(struct node));
    node->value = value;
    node->next = NULL;
}

void node_free(struct node *n) {
    free(n);
}

void llist_insert_head(struct node **head, struct node *n);
struct node *llist_delete_head(struct node **head);
void llist_insert_tail(struct node **head, struct node *n);
void llist_print(struct node *head);
void llist_free(struct node **head);




