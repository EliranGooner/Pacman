#include "Q2.h"

void display(chessPosList* lst)
{
	int numOfPos, i;

	ListWithNoRepeats(lst);

	numOfPos = sizeOfLst(lst);

	chessPosCell* curr = lst->head;

	char** board = buildBoard();

	for (i = 1; i <= numOfPos; i++)
	{
		enterPosToBoard(i, curr->position, board);
		curr = curr->next;
	}

	printf("\n# THE GAME BOARD # \n");
	printBoard(board);

	freeBoard(board);
}

int sizeOfLst(chessPosList* lst)
{
	chessPosCell* curr = lst->head;

	int size = 0;

	while (curr != NULL)
	{
		size++;
		curr = curr->next;
	}
	return size;
}

void removePosFromLst(chessPosCell* prev)
{
	chessPosCell* toDelete;

	toDelete = prev->next;

	prev->next = toDelete->next;

	free(toDelete);
}

void enterPosToBoard(int ind, chessPos pos, char** board)
{
	char r = pos[0], c = pos[1], i = ind + '0';
	int row = r - 64, col = c - 48;
	board[row][col] = i;
}

void emptyBoardRow(char** board, int i)
{
	int j;

	for (j = 1; j <= colSize; j++)
	{
		board[i][j] = ' ';
	}
}

char** buildBoard()
{
	int i;
	char num = 1, ch = 'A';
	char** board = (char**)malloc(sizeof(char*) * (rowSize + 1));
    checkMemoryFail(board);

	for (i = 0; i <= rowSize; i++)
	{
		board[i] = (char*)malloc(sizeof(char) * (rowSize + 1));
        checkMemoryFail(board[i]);
	}

	assert(board);

	for (i = 0; i <= rowSize; i++)
	{
		assert(board[i]);
	}


	for (i = 1; i <= rowSize; i++)
	{
		emptyBoardRow(board, i);
	}

	return board;
}

void printBoard(char** board)
{
	int i;

	printSepLine();
	printHeadline();

	for (i = 1; i <= rowSize; i++)
	{
		printSepLine();
		printLine(i, board);
	}

	printSepLine();
}

void printSepLine()
{
	int i, j;

	for (i = 0; i <= rowSize; i++)
	{
		printf("%c", CROSS);
		for (j = 0; j < 4; j++)
		{
			printf("%c", LINE);
		}
	}
	printf("%c\n", CROSS);
}

void printHeadline()
{
	int i;

	for (i = 0; i <= rowSize; i++)
	{
		printf("%c", BAR);
		if (i == 0)
		{
			printf("    ");
		}
		else
		{
			printf("  %d ", i);
		}
	}
	printf("%c\n", BAR);
}

void printLine(int i, char** board)
{
	int j;

	for (j = 0; j <= rowSize; j++)
	{
		printf("%c", BAR);

		if (j == 0)
		{
			printf("  %c ", ('A' + i - 1));
		}
		else if (board[i][j] > '9')
		{
			printf(" %d ", board[i][j] - '0');
		}
		else
		{
			printf("  %c ", board[i][j]);
		}
	}
	printf("%c\n", BAR);
}

void freeBoard(char** board)
{
	int i;

	for (i = 0; i <= rowSize; i++)
	{
		free(board[i]);
	}

	free(board);
}

void ListWithNoRepeats(chessPosList* lst)
{
	int i, j;
	int matt[rowSize][colSize];
	int row, col;
	chessPosCell* prev;
	chessPosCell* curr = lst->head;

	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < colSize; j++)
		{
			matt[i][j] = FALSE;
		}
	}

	row = curr->position[0] - 'A';
	col = curr->position[1] - '1';

	matt[row][col] = TRUE;

	prev = curr;
	curr = curr->next;

	while (curr != NULL)
	{
		if (isInMatt(curr->position, matt) == TRUE)
		{
			removePosFromLst(prev);

			curr = prev->next;
		}
		else
		{
			row = curr->position[0] - 'A';
			col = curr->position[1] - '1';

			matt[row][col] = TRUE;

			prev = curr;
			curr = curr->next;
		}
	}
}

int isInMatt(chessPos position, int matt[rowSize][colSize])
{
	int row=0, col=0;
	row = position[0] - 'A';
	col = position[1] - '1';

	if (matt[row][col] == TRUE)
		return TRUE;

	return FALSE;
}