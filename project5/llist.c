#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

int main (int argc, char *argv[]) {
    struct node *head = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "ih") == 0) {
            llist_insert_head(&head, node_alloc(atoi(argv[i+1])));
            i++;
        } 
        else if (strcmp(argv[i], "it") == 0) {
            llist_insert_tail(&head, node_alloc(atoi(argv[i+1])));
            i++;
        } 
        else if (strcmp(argv[i], "dh") == 0) {
            llist_delete_head(&head);
        }
        else if (strcmp(argv[i], "f") == 0) {
            llist_free(&head);
        }
        else if (strcmp(argv[i], "p") == 0) {
            llist_print(head);
        }
        // else {
        //     printf("Invalid command. Please choose either: ih, it, dh, f, or p.");
        //     exit(1);
        // }
    }
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
        while (current != NULL) {  // traverse nodes until last node and print each value
        printf("%d -> ", current->value);
        current = current->next;
        }
    }  
}

void llist_insert_head(struct node **head, struct node *n) {
    n->next = *head;
    *head = n;
}


struct node *llist_delete_head(struct node **head) {
    struct node *temp = *head; // save head and store in temp
    *head = (*head)->next; // change original head to be next node
    return temp; 
}
void llist_insert_tail(struct node **head, struct node *n) {
    if (*head == NULL) {    // if no head, set new node as hrad
        *head = n;
    } else {
         struct node *temp = *head;
        while (temp->next != NULL) {    //traverse nodes until last node
            temp = temp->next;       
        }
        temp->next = n; // set last node's next to be new node
    }     
}

void llist_free(struct node **head) {
    if (*head == NULL) {
        printf("No nodes.");
        exit(1);
    } else {
        while (*head != NULL) {
            struct node *temp = *head;  // make a temp node to store head
            *head = (*head)->next;  // change head to be next node
            node_free(temp);  // free temp
        }
    }

}




