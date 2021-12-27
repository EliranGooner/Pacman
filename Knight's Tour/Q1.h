#ifndef FINAL_PROJECT_Q1_H
#define FINAL_PROJECT_Q1_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#define rowSize 5
#define colSize 5

typedef char chessPos[2];

typedef struct _chessPosArray {
    unsigned int size;
    chessPos *positions;
} chessPosArray;

/* Creates a chess board with each cell containing the possible moves from it. */
chessPosArray*** validKnightMoves();
/* Checks how many moves are available from cell, insert them to the positions array and returns the moves' amount. */
unsigned int moveChecker(chessPos *positions, int currRow, int currCol);
/* Inserts the position to the position array. */
void assignSquare(chessPos *positions, int currRow, int rowChange, int currCol, int colChange, int *currInd, unsigned int *amountOfMoves);
/* Shrinks array to the given size. */
chessPos * shrinkArr(chessPos *orgArr, unsigned int newSize);
/* Frees the pointers array. */
void freeKnightMoves(chessPosArray ***possibleMoves);
/* Free the positions array. */
void freePosArr(chessPosArray *posArr);
#endif
