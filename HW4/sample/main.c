#include <stdio.h>
#include <stdlib.h>


int main() {
    char **suggestions;
    int i;

    struct Tree t = TREE_new();
    TREE_insert(&t, "hello");
    TREE_insert(&t, "hell");
    TREE_insert(&t, "helloween");

    suggestions = TREE_search(&t, "h");
    if (suggestions != NULL) {
        for (i = 0; suggestions[i] != NULL; ++i) {
            puts(suggestions[i]);
            free(suggestions[i]);
        }
        free(suggestions);
    }
    puts("----");

    suggestions = TREE_search(&t, "hell");
    if (suggestions != NULL) {
        for (i = 0; suggestions[i] != NULL; ++i) {
            puts(suggestions[i]);
            free(suggestions[i]);
        }
        free(suggestions);
    }
    puts("----");

    suggestions = TREE_search(&t, "hello");
    if (suggestions != NULL) {
        for (i = 0; suggestions[i] != NULL; ++i) {
            puts(suggestions[i]);
            free(suggestions[i]);
        }
        free(suggestions);
    }
    puts("----");

    suggestions = TREE_search(&t, "helloween");
    if (suggestions != NULL) {
        for (i = 0; suggestions[i] != NULL; ++i) {
            puts(suggestions[i]);
            free(suggestions[i]);
        }
        free(suggestions);
    }
    puts("----");
    return 0;
}
