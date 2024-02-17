#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* will play a move and also check if its a legal move.
   Returns 0 for true, 1 for false */
int move() {
    return 0;
}


int main(int argc, char *argv[]) {
    /* moved all var declarations to the top to avoid C90 warning */
    FILE *ptr = fopen(argv[1], "r");
    char c;

    /* read input file */
    if (argc == 1) {
        printf("No input provided. Terminating program.\n");
        exit(1);
    }
    
    if(ptr == NULL) {
        printf("File cannot be opened. Terminating program.\n");
        exit(1);
    }

    /*
    int pit1;
    int pit2;
    int pit3;
    int pit4;
    int pit5;
    int pit6;
    int pit7;
    int pit8;
    int pit9;
    int pit10;
    int pit11;
    int pit12;
    */ 


    /* print the file */
    while((c = fgetc(ptr)) != EOF) {
        if (c == ' ' || c == '\n') {
            continue;
        }
        printf("%c", c);
    }
    fclose(ptr);
    return 0;

    /* check input file constraints(valid input etc.) */

    /* play one move at a time, checking if its valid */
    /* check for any game stopages (win, tie, or no end) */

    /* output results */
}