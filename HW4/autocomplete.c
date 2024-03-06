#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int terminal;
    struct Node *parent;
    char transition;
    struct Node *children[16];
};

struct Tree {
    struct Node *root;
};


struct Tree TREE_new(void) {
    /* construct an empty tree */
    struct Tree tree;
    tree.root = NULL;
    /*tree.root->parent = NULL;*/
    return tree;
}

int TREE_empty(struct Tree *t) {
    /* return 1 if the tree contains no keys; otherwise 0 */
    return (t->root == NULL) ? 1 : 0;
}

void rClear(struct Node *node);
void TREE_clear(struct Tree *t) {
    /* remove all keys from the tree, and the root node */
    if (t->root == NULL) {
        return;
    }
    
    rClear(t->root);
    t->root = NULL;
}

void charToHex(char *key, char *hexArr);
struct Node* createNode(void);
void TREE_insert(struct Tree *t, char *key) {
    /* Insert a key into the tree */
    size_t i;
    int index;
    struct Node *curr = t->root;
    char *hexKey = malloc(strlen(key) * 2 + 1);
    /*create a char arr with double the length of key + 1 (for \0)
    use charToHex to convert the key to hex and modify hexKey */

    charToHex(key, hexKey);

    if(t->root == NULL) {
        t->root = createNode();
        curr = t->root;
    }

    for(i = 0; i < strlen(hexKey); i++) {
        index = hexKey[i] % 16;
        if(curr->children[index] == NULL) {
            curr->children[index] = createNode();
            curr->children[index]->parent = curr; /* set the parent */
            curr->children[index]->transition = hexKey[i];
            /*printf("INSERTING: %c\n", curr->children[index]->transition);*/

        }
        curr = curr->children[index];  /* Update current node */
    }
    free(hexKey);
}

/*
int TREE_contains(struct Tree *t, char *key) {
    // return 1 if the tree contains the key; otherwise 0 
}

void TREE_remove(struct Tree *t, char *key) {
    // Remove the key from the tree; trim the leaves when possible
}

char **TREE_search(struct Tree *t, char *str) {
    // 
    // Search for all keys starting with str
    // Return an array of strings; the last pointer is NULL
    //
}
*/

/* helper functions */
void rClear(struct Node *node) {
        /*calls recursive clear and deletes on each child until it reaches leaf 
        in which case it simply cant call recursive clear*/
    int i;
    if (node == NULL) {
        return;
    }

    for(i=0; i<16; i++) { 
        rClear(node->children[i]); 
    }

    /*printf("DELETING: %c\n", node->transition);*/
    free(node);
}

struct Node* createNode(void) {
    /*creates a blank node with children set to NULL*/
    int j;
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }

    newNode->terminal = 0;
    newNode->parent = NULL;

    for(j = 0; j < 16; j++) {
        newNode->children[j] = NULL;
    }
    return newNode;
}

void charToHex(char *key, char *hexArr) {
    /*void bcuz we just modifying the hex array*/
    while (*key != '\0') {
        sprintf(hexArr, "%02X", (unsigned int)*key);
        hexArr += 2;
        key++;
    }
    *hexArr = '\0'; /*wont overwrite bcuz dereference and we inceremented hexarr by 2 in loop*/

}



int main() {
    struct Tree myTree = TREE_new();

    TREE_insert(&myTree, "m");

    /*printf("Tree empty? 1=yes, 0=no=>> %d", TREE_empty(&myTree));*/
    
    /*puts("\n------------\n");*/

    TREE_clear(&myTree);

    return 0;
}
