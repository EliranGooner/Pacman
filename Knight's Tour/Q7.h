#ifndef FINAL_PROJECT_Q7_H
#define FINAL_PROJECT_Q7_H
#include <stdbool.h>
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"
#include "Q6.h"

/* Directs each input to its' relevant function. */
void sectionOperator();
/* Prints the main menu. */
void printMenu();
/* Receives an option from the user. */
int receiveOptionFromUser();
/* Receives a file name from user and returns it. */
char* getFileName();
/* Receives a knight's starting position from the user. */
void option1(chessPos* pos);
/* Creates a tree with all possible knight paths. */
void option2(chessPos* kPos, pathTree* tree);
/* Finds a knight path covering all board */
void option3(chessPos* kPos, pathTree* pathT, chessPosList** posList);
/* Creates a binary file and saves the knight's path that covers all the board to the file. */
void option4(chessPos* kPos, pathTree* pathT, chessPosList* posList);
/* Prints the path from the file. */
void option5();

#endif