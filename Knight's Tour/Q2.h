#ifndef FINAL_PROJECT_Q2_H
#define FINAL_PROJECT_Q2_H
#include "Q1.h"
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define BAR '|'
#define CROSS '+'
#define LINE '-'

typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList {
	chessPosCell *head;
	chessPosCell *tail;
} chessPosList;

/* Receives a chessPosList, it deletes the duplicated values, and then it prints 8X8 board with the numbered positions. */
void display(chessPosList* lst);
/* Returns the size of the list. */
int sizeOfLst(chessPosList* lst);
/* Removse positions from the list. */
void removePosFromLst(chessPosCell* prev);
/* Inserts positions to the board. */
void enterPosToBoard(int ind, chessPos pos, char** board);
/* Creates an empty board row. */
void emptyBoardRow(char** board, int i);
/* Builds a board and returns it. */
char** buildBoard();
/* Prints the board to the user. */
void printBoard(char** board);
/* Prints the seperating line. */
void printSepLine();
/* Prints the head line. */
void printHeadline();
/* Print each line in the board. */
void printLine(int i, char** board);
/* Free the board's memory allocations. */
void freeBoard(char** board);
/* Updates the board the way that the are only one of each position. */
void ListWithNoRepeats(chessPosList* lst);
/* Checks if the position is in the boolean matrix. */
int isInMatt(chessPos position, int matt[rowSize][colSize]);


#endif