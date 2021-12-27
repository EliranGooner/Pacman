#ifndef FINAL_PROJECT_Q4_H
#define FINAL_PROJECT_Q4_H
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"

/* Traverses the positions board to find a path to goes through every position on the board. */
chessPosList* findKnightPathCoveringAllBoard(pathTree *path_tree);
/* Creates empty list of positions. */
void createEmptyList(chessPosList *lst);
/* Recursive helper function that looks for a path covering all the board. Returns T/F based on findings. */
bool findPathRec(treeNode* node, chessPosArray *visited);
/* Creates a list from a positions array. */
void createPathList(chessPosList* lst, chessPosArray* visited);
/* Creates a new node from a position and inserts to the end of a given list. */
void insertDataToEndList(chessPosList* lst, chessPos position);
/* Creates a new node from a position. */
chessPosCell* createNewListNode(chessPos position, chessPosCell* next);
/* Inserts to the end of a given list. */
void insertNodeToEndList(chessPosList *lst, chessPosCell *newTail);
/* Checks if positions list is empty. */
bool isListEmpty(chessPosList *lst);
/* Frees the positions list. */
void freeList(chessPosList* lst);
#endif
