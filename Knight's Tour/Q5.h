#ifndef FINAL_PROJECT_Q5_H
#define FINAL_PROJECT_Q5_H
#include "Q1.h"
#include "Q2.h"

#define byteSIZE 8
typedef unsigned char BYTE;

void saveListToBinFile(char* file_name, chessPosList* pos_list);
/* Converts char to BYTE format (row of the pos). */
BYTE charToByte(char ch);
/* Converts char to BYTE format (col of the pos). */
BYTE numToByte(char ch);
/* Returns the number of byte needed for the given size of the pos list. */
int numberOfBytes(short size);
/* Inserts the positions to a BYTE array:
   Every pos will be represented by 6 bits, the 3 left bits represent the number of rows and the 3 right bits represent the number of cols. */
void insertPosToBinArr(BYTE* binArr, chessPosCell* head);
/* Executes one of the three options to act with the given number of space in the BYTE. */
void spaceOptions(BYTE* binArr, int* i, int* countBit, int* spaceLeft, BYTE posByte);
#endif