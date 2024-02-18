#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void printBoard(int pit1, int pit2, int pit3, int pit4, int pit5, int pit6, int pit7, int pit8, int pit9, int pit10, int pit11, int pit12, int northScore, int southScore) {
    printf("        Pits and Pebbles\n");
    printf("        ----------------\n\n");
    printf("             North\n\n");
    printf("  12   11   10    9    8    7\n");
    printf("+----+----+----+----+----+----+\n");
    printf("| %2d | %2d | %2d | %2d | %2d | %2d |    North %2d\n", pit12, pit11, pit10, pit9, pit8, pit7, northScore);
    printf("+----+----+----+----+----+----+\n");
    printf("| %2d | %2d | %2d | %2d | %2d | %2d |    South %2d\n",  pit1, pit2, pit3, pit4, pit5, pit6, southScore);
    printf("+----+----+----+----+----+----+\n");
    printf("   1    2    3    4    5    6\n\n");
    printf("             South\n");

    if(northScore > southScore && northScore > 24) {
        printf("North wins!\n");
    }
    else if(northScore < southScore && southScore > 24) {
        printf("South wins!\n");
    }
    else if(northScore == southScore && northScore > 0) {
        printf("It's a tie!\n");
    }
}

void move(int *pit1, int *pit2, int *pit3, int *pit4, int *pit5, int *pit6, int *pit7, int *pit8, int *pit9, int *pit10, int *pit11, int *pit12, int *northScore, int *southScore, int *currPlayer, int *nextMove) {
    /* currPlayer; 1 is north, 0 is south*/
    int pebbles;
    int i;
    int board[12];
    int collected = 0;
    int northTempScore = *northScore;
    int southTempScore = *southScore;

    board[0] = *pit1;
    board[1] = *pit2;
    board[2] = *pit3;
    board[3] = *pit4;
    board[4] = *pit5;
    board[5] = *pit6;
    board[6] = *pit7;
    board[7] = *pit8;
    board[8] = *pit9;
    board[9] = *pit10;
    board[10] = *pit11;
    board[11] = *pit12;
    i = *nextMove - 1; /*get the index to start from for later. 
    MODULUS SO THAT WE CAN GO FROM 12 to 1(12 mod 12 = 1)!!!! this is the first time modulus has
    come in handy outside of math!*/
    pebbles = board[i]; /*-1 buz index starts at 0*/
    board[i] = 0; /* empty pit bcuz we picked up pebbles*/

    while (pebbles > 0) {
        i = (i + 1) % 12; /*start dropping after the pit we picked up*/
        board[i]++;
        pebbles--;
        if ((board[i] == 2 || board[i] == 3) && ((*currPlayer == 1 && i <= 6) || (*currPlayer == 0 && i >= 7))) {
            if (*currPlayer == 1) {
                collected++;
                *northScore += board[i];
                board[i] = 0;

                while ((board[(i - 1 + 12) % 12] == 2) || board[(i - 1 + 12) % 12] == 3) {
                    *northScore += board[(i - 1 + 12) % 12];
                    board[(i - 1 + 12) % 12] = 0;
                }            
                if (collected == 6) {
                    *northScore = northTempScore;
                    board[0] = *pit1;
                    board[1] = *pit2;
                    board[2] = *pit3;
                    board[3] = *pit4;
                    board[4] = *pit5;
                    board[5] = *pit6;
                    board[6] = *pit7;
                    board[7] = *pit8;
                    board[8] = *pit9;
                    board[9] = *pit10;
                    board[10] = *pit11;
                    board[11] = *pit12;
                }
            }
            else {
                *southScore += board[i];
                collected++;
                board[i] = 0;

                while ((board[(i - 1 + 12) % 12] == 2) || board[(i - 1 + 12) % 12] == 3) {
                    *southScore += board[(i - 1 + 12) % 12];
                    board[(i - 1 + 12) % 12] = 0;
                }
                if (collected == 5) {
                    *southScore = southTempScore;
                    board[0] = *pit1;
                    board[1] = *pit2;
                    board[2] = *pit3;
                    board[3] = *pit4;
                    board[4] = *pit5;
                    board[5] = *pit6;
                    board[6] = *pit7;
                    board[7] = *pit8;
                    board[8] = *pit9;
                    board[9] = *pit10;
                    board[10] = *pit11;
                    board[11] = *pit12;

                }
            }
        }

    }
    printf("Collected: %d", collected);
    /*update the pits*/
    *pit1 = board[0];
    *pit2 = board[1];
    *pit3 = board[2];
    *pit4 = board[3];
    *pit5 = board[4];
    *pit6 = board[5];
    *pit7 = board[6];
    *pit8 = board[7];
    *pit9 = board[8];
    *pit10 = board[9];
    *pit11 = board[10];
    *pit12 = board[11];
}

int main(int argc, char *argv[]) {
    /* moved all var declarations to the top to avoid C90 warning */
    FILE *ptr = fopen(argv[1], "r");
    char c;
    char nextC;
    int pit1 = 4, pit2 = 4, pit3 = 4, pit4 = 4, pit5 = 4, pit6 = 4, pit7 = 4, pit8 = 4, pit9 = 4, pit10 = 4, pit11 = 4, pit12 = 4;
    int newGame = 0;
    int southScore = 0;
    int northScore = 0;
    int size;
    int nextMove = 0;
    int currPlayer = 1; /* 0 is north, 1 is south*/

    /* read input file */
    if (argc == 1) {
        printf("No input provided. Terminating program.\n");
        exit(1);
    }
    
    if (ptr == NULL) {
        printf("File cannot be opened. Terminating program.\n");
        exit(1);
    }
    fseek(ptr, 0, SEEK_END);
    size = ftell(ptr);
    rewind(ptr);
    if (size == 0) {
        printBoard (pit1, pit2, pit3, pit4, pit5, pit6, pit7, pit8, pit9, pit10, pit11, pit12, northScore, southScore);
        exit(1);
    }

    /* read file, checks for white spaces and numbers accordingly*/
    while((c = fgetc(ptr)) != EOF) {
        if (c == ' ' || c == '\n') {
            continue;
        }
        else if (c == 'p' || c == 'P') {
            newGame = 1;
            fscanf(ptr, "%d %d %d %d %d %d", &pit1, &pit2, &pit3, &pit4, &pit5, &pit6);
            fscanf(ptr, "%d %d %d %d %d %d", &pit12, &pit11, &pit10, &pit9, &pit8, &pit7);
            fscanf(ptr, "%d %d", &southScore, &northScore);
        }
        else if (c == 's') {
            nextC = fgetc(ptr);
            if (nextC == ' ' || nextC == '\n') {
                while (fscanf(ptr, "%d", &nextMove) == 1) {
                    if (nextMove <= 6 && nextMove >= 1) {
                        currPlayer = 0;
                    }
                    else if (nextMove <= 12 && nextMove >= 6) {
                        currPlayer = 1;
                    }
                    else {
                        continue;
                    }
                    move(&pit1, &pit2, &pit3, &pit4, &pit5, &pit6, &pit7, &pit8, &pit9, &pit10, &pit11, &pit12, &northScore, &southScore, &currPlayer, &nextMove);
                }
            }
        }
        else if (newGame == 0) {
            continue;
        }
    }

    printBoard (pit1, pit2, pit3, pit4, pit5, pit6, pit7, pit8, pit9, pit10, pit11, pit12, northScore, southScore);
    fclose(ptr);
    return 0;

}