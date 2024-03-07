#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int terminal;
    struct Node *parent;
    int transition;
    struct Node *children[16];
};

struct Tree {
    struct Node *root;
};

struct Tree TREE_new(void) {
    /* construct an empty tree */
    struct Tree tree;
    tree.root = NULL;
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

    charToHex(key, hexKey);

    if(t->root == NULL) {
        t->root = createNode();
        curr = t->root;
    }
    for(i = 0; i < strlen(hexKey); i++) {
        index = hexKey[i] % 16;
        if(curr->children[index] == NULL) {
            curr->children[index] = createNode();
            curr->children[index]->parent = curr; 
            curr->children[index]->transition = hexKey[i];
            /* printf("INSERTING: %c\n", curr->children[index]->transition); */
        }
        curr = curr->children[index]; 
    }
    curr->terminal = 1;
    free(hexKey);
}

int TREE_contains(struct Tree *t, char *key) {
    /* return 1 if the tree contains the key; otherwise 0 */
    struct Node *currNode = t->root;
    int index;
    char *hexKey = malloc(strlen(key) * 2 + 1);
    char *hexKeyStart;
    if (t->root == NULL) {
        return 0;
    }
    if (hexKey == NULL) {
        exit(EXIT_FAILURE);
    }
    charToHex(key, hexKey);
    hexKeyStart = hexKey;  /* Store the start of memory */

    while(*hexKey != '\0') {
        index = *hexKey % 16;
        if (currNode->children[index] == NULL) {
            free(hexKeyStart); 
            return 0;
        }
        currNode = currNode->children[index];
        hexKey++;
    }
    free(hexKeyStart); 
    return (currNode->terminal == 1) ? 1 : 0;
}

void TREE_remove(struct Tree *t, char *key) {
    /* Remove the key from the tree; trim the leaves when possible */
    struct Node *currNode = t->root;
    struct Node *pNode;
    int leaf = 1;
    int i;
    int index;
    int indx;
    char *hexKey = malloc(strlen(key) * 2 + 1);
    char *hexKeyStart;
    
    if (t->root == NULL) { /* empty tree */
        free(hexKey);
        return;
    }
    if ((TREE_contains(t, key) == 0)) { /* key to remove isn't in the tree  */
        free(hexKey);
        return;
    }
    
    charToHex(key, hexKey); /* convert key to hexkey*/
    hexKeyStart = hexKey; /* store start so we don't lose in while incrementing*/
    /* start at the root and traverse tree based on chars in the key to find the key */
    while(*hexKey != '\0') {
        index = *hexKey % 16;
        if(currNode->children[index] == NULL) {
            free(hexKey);
            return; /* key not found */
        }
        currNode = currNode->children[index]; /*if child contains the key, move to the child*/
        hexKey++;
    }
    /* if the node is a leaf, remove upwards until another terminal is found or there is a parent with other children */
    for (i=0; i < 16 ;i++) {
        if(currNode->children[i] != NULL) {
            leaf = 0; /* set leaf to false if node */
            break;
        }
    }
    /* printf("Removing key: %s\n", key); */
    currNode->terminal = 0; /* if the node has children, set terminal to false (remove key from tree) */
    if(leaf && currNode != t->root) {
        pNode = currNode->parent;
        indx = currNode->transition % 16;
        pNode->children[indx] = NULL;

        while(pNode != t->root && pNode->terminal == 0) {
            currNode = pNode;
            pNode = pNode->parent;
            indx = currNode->transition % 16;
            pNode->children[indx] = NULL;
        }
    }
    free(hexKeyStart);
}
/*
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
    /* printf("DELETING: %c\n", node->transition); */
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
    while (*key != '\0') {
        sprintf(hexArr, "%02X", (unsigned int)*key);
        hexArr += 2;
        key++;
    }
    *hexArr = '\0';
}

int main() {
    struct Tree myTree = TREE_new();
    TREE_insert(&myTree, "can");
    TREE_insert(&myTree, "candy");
    TREE_insert(&myTree, "candyland");
    TREE_remove(&myTree, "can");
    printf("Tree empty? 1 is yes, 0 is no:: %d\n", TREE_empty(&myTree)); 
    printf("Tree has key CANDY? 1 is yes, 0 is no:: %d\n", TREE_contains(&myTree, "candy"));
    /*printf("Tree empty BEFORE INSERTS? 1=yes, 0=no=>> %d\n", TREE_empty(&myTree)); 
    printf("Tree empty AFTER REMOVING ONE KEY? 1=yes, 0=no=>> %d\n", TREE_empty(&myTree)); 
    TREE_insert(&myTree, "helloween");
    TREE_insert(&myTree, "hello my name is jeff");
    printf("Tree has key HELLO? %d\n", TREE_contains(&myTree, "hello"));
    printf("Tree has key HE? %d\n", TREE_contains(&myTree, "he")); 
    printf("Tree has key HELLOWEEN? %d\n", TREE_contains(&myTree, "help")); 0
    printf("Tree empty AFTER CLEARING? 1=yes, 0=no=>> %d\n", TREE_empty(&myTree)); 
    */
    
    /* puts("\n------------\n"); */

    TREE_clear(&myTree);

    return 0;
}
