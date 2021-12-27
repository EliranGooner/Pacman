#include "Q3.h"

pathTree findAllPossibleKnightPaths(chessPos *startingPosition)
{
    pathTree tree;
    chessPosArray *visited, ***possibleMoves;

    possibleMoves = validKnightMoves();
    visited = (chessPosArray*)malloc(sizeof(chessPosArray));
    checkMemoryFail(visited);
    visited->size = 0;
    tree.root = (treeNode*)malloc(sizeof(treeNode));
    checkMemoryFail(tree.root);
    tree.root->position[0] = (*startingPosition)[0];
    tree.root->position[1] = (*startingPosition)[1];
    tree.root->next_possible_positions = NULL;
    buildTreeRec(tree.root,possibleMoves,visited);
    freePosArr(visited);
    freeKnightMoves(possibleMoves);
    return tree;
}


void buildTreeRec(treeNode *node, chessPosArray*** possibleMoves, chessPosArray *visited)
{
    int i,j;
    unsigned int prevVisitedSize;
    chessPosArray* movesArr = NULL;
    treeNode *newTreeNode;
    treeNodeListCell *newListNode, *currListNode = NULL;
    bool isFirstChild = true;

    for (i = 0; i < (node->position[0] - 16) - '0'; i++)
    {
        for(j = 0; j < (node->position[1] - '0'); j++)
        {
            movesArr = possibleMoves[i][j];
        }
    }

    for (i = 0; i < (movesArr ? movesArr->size : 0); i++)
    {
        if (!isVisited(movesArr->positions[i],visited))
        {
            newTreeNode = (treeNode*)malloc(sizeof(treeNode));
            checkMemoryFail(newTreeNode);
            newListNode = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
            checkMemoryFail(newListNode);
            newTreeNode->position[0] = movesArr->positions[i][0];
            newTreeNode->position[1] = movesArr->positions[i][1];
            newTreeNode->next_possible_positions = NULL;
            newListNode->node = newTreeNode;
            newListNode->next = NULL;

            if (isFirstChild)
            {
                node->next_possible_positions = newListNode;
                currListNode = newListNode;
                isFirstChild = false;
            }
            else
            {
                currListNode->next = newListNode;
                currListNode = currListNode->next;
                currListNode->next = NULL;
            }

            prevVisitedSize = visited->size;
            extendVisited(visited);
            visited->positions[visited->size - 1][0] = node->position[0];
            visited->positions[visited->size - 1][1] = node->position[1];
            buildTreeRec(newTreeNode,possibleMoves,visited);
            trimVisited(visited,prevVisitedSize);
        }
    }
}

bool isVisited(chessPos position, chessPosArray *visitedArr)
{
    int i;
    bool visited = false;
    for (i = 0; i < visitedArr->size; i++)
    {
        if (position[0] == visitedArr->positions[i][0] && position[1] == visitedArr->positions[i][1])
            visited = true;
    }
    return visited;
}

void extendVisited(chessPosArray* visited)
{
    int i;
    chessPos *extendedVisitedArr = (chessPos*)malloc((visited->size + 1) * sizeof(chessPos));
    checkMemoryFail(extendedVisitedArr);

    if (visited->size > 0)
    {
        for (i = 0; i < visited->size; i++) {
            extendedVisitedArr[i][0] = visited->positions[i][0];
            extendedVisitedArr[i][1] = visited->positions[i][1];
        }
        free(visited->positions);
    }
    visited->positions = extendedVisitedArr;
    visited->size++;
}

void trimVisited(chessPosArray* visited, unsigned int newSize)
{
    int i;
    chessPos *trimmedVisitedArr = (chessPos*)malloc(newSize * sizeof(chessPos));
    checkMemoryFail(trimmedVisitedArr);
    for (i = 0; i < newSize; i++)
    {
        trimmedVisitedArr[i][0] = visited->positions[i][0];
        trimmedVisitedArr[i][1] = visited->positions[i][1];
    }
    free(visited->positions);
    visited->positions = trimmedVisitedArr;
    visited->size = newSize;
}

void freeTree(pathTree tr)
{
    freeTreeRec(tr.root);
}

void freeTreeRec(treeNode* node)
{
	treeNodeListCell *nextPosMove, *tempPosMove;

	if (node == NULL || node->next_possible_positions == NULL)
		return;

	nextPosMove = node->next_possible_positions;;
	while (nextPosMove != NULL)
	{
		freeTreeRec(nextPosMove->node);
		tempPosMove = nextPosMove->next;
        free(nextPosMove);
        nextPosMove = tempPosMove;
    }
    free(nextPosMove);
	free(node);
}
