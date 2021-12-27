#ifndef FINAL_PROJECT_Q6_H
#define FINAL_PROJECT_Q6_H
#include "Q1.h"
#include "Q2.h"
#include "Q4.h"
#include "Q5.h"

/* Receives a binary file's name and reads the list written in it and returns integers based on the list's validity and length. */
int checkAndDisplayPathFromFile(char* file_name);
/* Reads positions from the binary file to the positions list. */
void readPositionsIntoList(FILE* f, chessPosList* lst, short int positionsAmount);
/* Set a position from byte with zero bit offset. */
chessPos* setCurrPos0(BYTE *posBytes, int byteCount);
/* Set a position from byte with 2 bits offset. */
chessPos* setCurrPos2(BYTE *posBytes, int byteCount);
/* Set a position from byte with 4 bits offset. */
chessPos* setCurrPos4(BYTE *posBytes, int byteCount);
/* Set a position from byte with 6 bits offset. */
chessPos* setCurrPos6(BYTE *posBytes, int byteCount);
/* Checks if path list is valid. */
bool checkValidPath(chessPosList* lst);
/* Checks if path covers all board */
bool checkPathCoversAllBoard(chessPosList* lst);
#endif
