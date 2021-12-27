#include "Q4.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree *path_tree)
{
    chessPosList *lst = NULL;
    chessPosArray* visited;

    lst = (chessPosList*)malloc(sizeof(chessPosList));
    createEmptyList(lst);
    visited = (chessPosArray*)malloc(sizeof(chessPosArray));
    checkMemoryFail(visited);
    visited->size = 0;

    if (findPathRec(path_tree->root,visited))
    {
        createPathList(lst,visited);
        return lst;
    }
    else
        return NULL;
}

bool findPathRec(treeNode* node, chessPosArray *visited)
{
    unsigned int prevVisitedSize;
    treeNodeListCell *currChild = node ? node->next_possible_positions : NULL;

    while (currChild != NULL)
    {
        prevVisitedSize = visited->size;
        extendVisited(visited);
        visited->positions[visited->size - 1][0] = node->position[0];
        visited->positions[visited->size - 1][1] = node->position[1];
        if (visited->size == (rowSize * colSize - 1))
        {
            extendVisited(visited);
            visited->positions[visited->size - 1][0] = node->next_possible_positions->node->position[0];
            visited->positions[visited->size - 1][1] = node->next_possible_positions->node->position[1];
            return true;
        }
        if (findPathRec(currChild->node,visited))
        {
            return true;
        }
        trimVisited(visited,prevVisitedSize);
        currChild = currChild->next;
    }

    return false;
}

void createPathList(chessPosList* lst, chessPosArray* posArr)
{
    int i;
    chessPos position;

    for (i = 0; i < posArr->size; i++)
    {
        position[0] = posArr->positions[i][0];
        position[1] = posArr->positions[i][1];
        insertDataToEndList(lst, position);
    }

    freePosArr(posArr);
}

void insertDataToEndList(chessPosList* lst, chessPos position)
{
    chessPosCell* newTail;

    newTail = createNewListNode(position, NULL);
    insertNodeToEndList(lst, newTail);
}

chessPosCell* createNewListNode(chessPos position, chessPosCell* next)
{
    chessPosCell* newNode = (chessPosCell*)malloc(sizeof(chessPosCell));

    checkMemoryFail(newNode);
    newNode->position[0] = position[0];
    newNode->position[1] = position[1];
    newNode->next = next;
    return newNode;
}

void insertNodeToEndList(chessPosList *lst, chessPosCell *newTail)
{
    if (isListEmpty(lst))
    {
        lst->head = newTail;
        lst->tail = newTail;
    }
    else
    {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

bool isListEmpty(chessPosList *lst)
{
    if (lst->head)
        return false;
    else
        return true;
}


void createEmptyList(chessPosList *lst)
{
    lst->head = NULL;
    lst->tail = NULL;
}


void freeList(chessPosList* lst)
{
    chessPosCell *currCell = NULL, *next;
    if (lst != NULL)
    {
        currCell = lst->head;
        while (currCell != NULL)
        {
            next = currCell->next;
            free(currCell);
            currCell = next;
        }
    }
}

