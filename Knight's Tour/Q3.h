#ifndef FINAL_PROJECT_Q3_H
#define FINAL_PROJECT_Q3_H
#include "Q1.h"
#include <stdbool.h>
#include <string.h>

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
    chessPos position;
    treeNodeListCell *next_possible_positions;
} treeNode;

struct _treeNodeListCell {
    treeNode *node;
    struct _treeNodeListCell *next;
};

typedef struct _pathTree {
    treeNode *root;
} pathTree;

/* Returns a tree formed by all the possible moves from given starting position. */
pathTree findAllPossibleKnightPaths(chessPos *startingPosition);
/* Recursive function that builds the positions tree. */
void buildTreeRec(treeNode *node, chessPosArray*** possibleMoves, chessPosArray *visited);
/* Checks if the given position has already been visited. */
bool isVisited(chessPos position, chessPosArray* visitedArr);
/* Extend the size of the visited array by one */
void extendVisited(chessPosArray* visited);
/* Trims the visited array size to the given amount. */
void trimVisited(chessPosArray* visited, unsigned int newSize);
/* Free the positions tree. */
void freeTree(pathTree tr);
/* Recursive helper function that frees the positions tree. */
void freeTreeRec(treeNode* node);
#endif
