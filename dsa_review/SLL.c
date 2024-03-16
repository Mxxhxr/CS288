#include <stdio.h>
#include <stdlib.h>


/* self-referential structure */
struct Node {
    int item;
    struct Node *next;
};

struct List {
    struct Node *head;
    struct Node *tail;
};


struct List SLL_new() {
    /* construct an empty list */
    struct List list;
    list.head = NULL;
    list.tail = NULL;
    return list;

}

int SLL_length(struct List *list) {
    /* return the number of items in the list */
    int length = 0;
    struct Node *node;
    
    for (node = list->head; node != NULL; node = node->next) {
        ++length;
    }
    return length;
}

int SLL_empty(struct List *list) {
    /* return true if the list contains no items */
    if (list->head == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

int SLL_contains(struct List *list, int item) {
    /* return true if the list contains the item */
    if (list->head == NULL) { /*more effecient than using SLL_empty() */
        return 0;
    }

    struct Node *n;

    for (n = list->head; n != NULL; n = n->next) {
        if (n->item == item) {
            return 1;
        }
    }
    return 0;
}

int SLL_pop(struct List *list) {
    /* remove and return the first item of the list */
    struct Node *n = list->head;
    int item = n->item;
    list->head = n->next;
    
    if (SLL_empty(list)) { /*is the list empty after popping?*/
        list->tail = NULL;
    }
    free(n);
    return item;
}

void SLL_clear(struct List *list) {
    /* remove all items from the list */
    while (!SLL_empty(list)) {
        SLL_pop(list);
    }
}

void SLL_push(struct List *list, int item) {
    /* insert the item at the front of the list */
    struct Node *n = malloc(sizeof(struct Node));
    n->item = item;
    n->next = list->head;
    if(SLL_empty(list)) {
        list->tail = n;
    }
    list->head = n;
}

void SLL_append(struct List *list, int item) {
    /* append the item to the end of the list */
    if (SLL_empty(list)) {
        SLL_push(list, item);
    }
    else {
        struct Node *n = malloc(sizeof(struct Node));
        n->item = item;
        n->next = NULL;
        list->tail->next = n;
        list->tail = n;
    }
}

int main() {
    int i;

    struct List list = SLL_new();
    for (i = 0; i < 5; ++i) {
        SLL_push(&list, i);
        SLL_append(&list, i);
    }

    while (!SLL_empty(&list)) {
        printf("%d\n", SLL_pop(&list));
    }

    return 0;
}