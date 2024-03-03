#include <stdio.h>
#include <stdlib.h>

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

/* basically inform the compiler that I have a helper function
declared below. not sure why i get errors when i move the whole 
functino up here. but if i do this and keep the function below 
it works fine. */
void TREE_clear_caller(struct Node *root); 

void TREE_clear(struct Tree *t) {
    /* remove all keys from the tree, and the root node */
    int i;
    struct Node *root = t->root;
    
    /* recursively delete nodes until root is empty. */
    if (root == NULL) {
        return;
    }
    else {
        for (i = 0; i < 16; i++) {
            if(root->children[i] !=NULL) {
                free(root->children[i]);
                TREE_clear_caller(t->root->children[i]);
            }
        }
        free(root);
        root = NULL; /* do this to break out of the recursion */
    }
}

void TREE_insert(struct Tree *t, char *key) {
    /* Insert a key into the tree */
}

int TREE_contains(struct Tree *t, char *key) {
    /* return 1 if the tree contains the key; otherwise 0 */
}

void TREE_remove(struct Tree *t, char *key) {
    /* Remove the key from the tree; trim the leaves when possible */
}

char **TREE_search(struct Tree *t, char *str) {
    /* 
    ** Search for all keys starting with str
    ** Return an array of strings; the last pointer is NULL
    */
}

void TREE_clear_caller(struct Node *root) {
    /* cannot do the recursiive call in tree_clear because 
    it expects a struct Tree but the recursive call parameter
    is of type struct*/
    TREE_clear((struct Tree *)root);
}


int main() {
    return 0;
}