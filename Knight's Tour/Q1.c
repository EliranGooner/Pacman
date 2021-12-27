#include "Q1.h"

chessPosArray *** validKnightMoves()
{
    int i, j;
    chessPosArray ***movesBoard;
    chessPosArray  *possibleMoves;
    chessPos *positions;

    movesBoard = (chessPosArray ***)malloc(rowSize * sizeof(chessPosArray**));
    checkMemoryFail(movesBoard);

    for (i = 0; i < rowSize; i++)
    {
        movesBoard[i] = (chessPosArray **)malloc(colSize * sizeof(chessPosArray*));
        checkMemoryFail(movesBoard[i]);
    }

    for (i = 0; i < rowSize; i++)
    {
        for(j = 0; j < colSize; j++)
        {
            possibleMoves = (chessPosArray *)malloc(sizeof(chessPosArray));
            checkMemoryFail(possibleMoves);
            movesBoard[i][j] = possibleMoves;
            positions = (chessPos *)malloc(8 * sizeof(chessPos));
            checkMemoryFail(positions);
            possibleMoves->positions = positions;
            possibleMoves->size = moveChecker(possibleMoves->positions, i, j);
            possibleMoves->positions = shrinkArr(possibleMoves->positions, possibleMoves->size);
        }
    }

    return movesBoard;
}

unsigned int moveChecker(chessPos *positions, int currRow, int currCol)
{
    unsigned int amountOfMoves = 0;
    int currInd = 0;

    if ((currRow - 2) >= 0 && (currCol + 1) < colSize)
    {
        assignSquare(positions,currRow,-2,currCol,1, &currInd,&amountOfMoves);
    }
    if ((currRow - 1) >= 0 && (currCol + 2) < colSize)
    {
        assignSquare(positions,currRow,-1,currCol,2, &currInd,&amountOfMoves);
    }
    if ((currRow + 1) < rowSize && (currCol + 2) < colSize)
    {
        assignSquare(positions,currRow,1,currCol,2, &currInd,&amountOfMoves);
    }
    if ((currRow + 2) < rowSize && (currCol + 1) < colSize)
    {
        assignSquare(positions,currRow,2,currCol,1, &currInd,&amountOfMoves);
    }
    if ((currRow + 2) < rowSize && (currCol - 1) >= 0)
    {
        assignSquare(positions,currRow,2,currCol,-1, &currInd,&amountOfMoves);
    }
    if ((currRow + 1) < rowSize && (currCol - 2) >= 0)
    {
        assignSquare(positions,currRow,1,currCol,-2, &currInd,&amountOfMoves);
    }
    if ((currRow - 1) >= 0 && (currCol - 2) >= 0)
    {
        assignSquare(positions,currRow,-1,currCol,-2, &currInd,&amountOfMoves);
    }
    if ((currRow - 2) >= 0 && (currCol - 1) >= 0)
    {
        assignSquare(positions,currRow,-2,currCol,-1, &currInd, &amountOfMoves);
    }

    return amountOfMoves;
}

void assignSquare(chessPos *positions, int currRow, int rowChange, int currCol, int colChange, int *currInd, unsigned int *amountOfMoves)
{
    positions[*currInd][0] = ((currRow + rowChange) + '0') + 17;

    if (colChange < 0)
        positions[*currInd][1] = ((currCol + colChange) + '0') + 1;
    else
        positions[*currInd][1] = (currCol + colChange + 1) + '0';

    *amountOfMoves += 1;
    *currInd += 1;
}

chessPos * shrinkArr(chessPos *orgArr, unsigned int newSize)
{
    unsigned int i;
    chessPos *newArr = (chessPos *)malloc(newSize * sizeof(chessPos));
    checkMemoryFail(newArr);
    for (i = 0; i < newSize; i++)
    {
        newArr[i][0] = orgArr[i][0];
        newArr[i][1] = orgArr[i][1];
    }
    free(orgArr);
    return newArr;
}

void freeKnightMoves(chessPosArray ***possibleMoves)
{
    int i,j;
    for (i = 0; i < rowSize; i++)
    {
        for (j = 0; j < colSize; j++)
        {
            freePosArr(possibleMoves[i][j]);
        }
        free(possibleMoves[i]);
    }
    free(possibleMoves);
}

void freePosArr(chessPosArray *posArr)
{
    free(posArr->positions);
    free(posArr);
}
