#include "Q6.h"

int checkAndDisplayPathFromFile(char* file_name)
{
    short int positionsAmount;
    chessPosList lst;

    FILE *f = fopen(file_name,"rb");
    if (f == NULL)
    {
        fclose(f);
        return -1;
    }

    createEmptyList(&lst);
    fread(&positionsAmount,sizeof(short int),1,f);
    readPositionsIntoList(f,&lst,positionsAmount);

    if (checkValidPath(&lst))
    {
        display(&lst);
        if (checkPathCoversAllBoard(&lst))
        {
            freeList(&lst);
            return 2;
        }
        freeList(&lst);
        return 3;
    }
    else
    {
        freeList(&lst);
        return 1;
    }
}

void readPositionsIntoList(FILE* f, chessPosList* lst, short int positionsAmount)
{
    int bitsAmount = positionsAmount * 6,posCount=0,byteCount=0;
    BYTE *posBytes = (BYTE*)malloc(bitsAmount * sizeof(bitsAmount));
    checkMemoryFail(posBytes);
    chessPos *newPos = NULL;

    while (bitsAmount % 8 != 0)
        bitsAmount++;

    posBytes = (BYTE*)malloc((bitsAmount / 8) * sizeof(BYTE));
    checkMemoryFail(posBytes);
    fread(posBytes,sizeof(BYTE),bitsAmount/8,f);

    while (posCount < positionsAmount)
    {
        if (posCount % 4 == 0)
            newPos = setCurrPos0(posBytes,byteCount);
        else if (posCount % 4 == 1)
        {
            newPos = setCurrPos6(posBytes, byteCount);
            byteCount++;
        }
        else if (posCount % 4 == 2)
        {
            newPos = setCurrPos4(posBytes,byteCount);
            byteCount++;
        }
        else if (posCount % 4 == 3)
        {
            newPos = setCurrPos2(posBytes, byteCount);
            byteCount++;
        }
        insertDataToEndList(lst,*newPos);
        free(newPos);
        posCount++;
    }

    free(posBytes);
}

chessPos* setCurrPos0(BYTE *posBytes, int byteCount)
{
    chessPos *pos = (chessPos*)malloc(sizeof(chessPos));
    checkMemoryFail(pos);
    int mask,currPos = 0,i;

    for (i = 0; i < 6; i++)
    {
        mask = (posBytes[byteCount] >> (8 - i - 1)) & 1;
        currPos = (currPos << 1) | mask;
        if (i == 2)
        {
            (*pos)[0] = currPos + 'A';
            currPos = 0;
        }
    }

    (*pos)[1] = currPos + '1';
    return pos;
}

chessPos* setCurrPos2(BYTE *posBytes, int byteCount)
{
    chessPos *pos = (chessPos*)malloc(sizeof(chessPos));
    checkMemoryFail(pos);
    int mask,currPos = 0,i;

    for (i = 0; i < 6; i++)
    {
        mask = (posBytes[byteCount] >> (6 - i - 1)) & 1;
        currPos = (currPos << 1) | mask;
        if (i == 2)
        {
            (*pos)[0] = currPos + 'A';
            currPos = 0;
        }
    }

    (*pos)[1] = currPos + '1';
    return pos;
}

chessPos* setCurrPos4(BYTE *posBytes, int byteCount)
{
    chessPos *pos = (chessPos*)malloc(sizeof(chessPos));
    checkMemoryFail(pos);
    int mask,currPos = 0,i;

    (*pos)[0] = ((posBytes[byteCount] >> 1) & 7) + 'A';

    mask = posBytes[byteCount] & 1;
    currPos = (currPos << 1) | mask;

    for (i = 0; i < 2; i++)
    {
        mask = (posBytes[byteCount+1] >> (8 - i - 1)) & 1;
        currPos = (currPos << 1) | mask;
    }

    (*pos)[1] = currPos + '1';
    return pos;
}

chessPos* setCurrPos6(BYTE *posBytes, int byteCount)
{
    chessPos *pos = (chessPos*)malloc(sizeof(chessPos));
    checkMemoryFail(pos);
    char mask,currPos = 0;
    int i;

    currPos = posBytes[byteCount] & 3;

    mask = posBytes[byteCount + 1] >> 7;
    currPos = (currPos << 1) | mask;
    (*pos)[0] = currPos + 'A';
    currPos = 0;

    for (i = 0; i < 3; i++)
    {
        mask = (posBytes[byteCount+1] >> (7 - i - 1)) & 1;
        currPos = (currPos << 1) | mask;
    }

    (*pos)[1] = currPos + '1';
    return pos;
}

bool checkValidPath(chessPosList* lst)
{
    int i,j;
    chessPosArray ***possibleMoves, *movesArr = NULL;
    chessPosCell *currNode = lst->head;
    possibleMoves = validKnightMoves();

    while (currNode->next != NULL)
    {
        for (i = 0; i <= (currNode->position[0] - 17) - '0'; i++) // added =
        {
            for (j = 0; j <= ((currNode->position[1] - 1) - '0'); j++) // added =
            {
                movesArr = possibleMoves[i][j];
            }
        } 

        for (i=0 ; i < movesArr->size; i++)
        {
            if (currNode->next->position[0] == movesArr->positions[i][0] && currNode->next->position[1] == movesArr->positions[i][1])
                return true;
        }
        currNode = currNode->next;
    }

    freeKnightMoves(possibleMoves);
    return false;
}

bool checkPathCoversAllBoard(chessPosList* lst)
{
    if (sizeOfLst(lst) == colSize * rowSize)
        return true;
    else
        return false;
}