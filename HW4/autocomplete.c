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
}

int TREE_empty(struct Tree *t) {
    /* return 1 if the tree contains no keys; otherwise 0 */
}

void TREE_clear(struct Tree *t) {
    /* remove all keys from the tree, and the root node */
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

int main() {
    return 0;
}
