#include "Q7.h"

void sectionOperator()
{
	int option = 0;
	bool flag = true;
	char* fileName = NULL;
	chessPos* kPos;
	pathTree pathT;		pathT.root = NULL;
	chessPosList* posList = NULL; 
	posList = (chessPosList*)calloc(1,sizeof(chessPosList));
	checkMemoryFail(posList);
	kPos = (chessPos*)calloc(1,sizeof(chessPos));
	checkMemoryFail(kPos);
	(*kPos)[0] = '0'; (*kPos)[1] = '0';
	
	printMenu();

	while (option != 6)
	{
		option = receiveOptionFromUser();

		switch (option)
		{
		case 1:
			option1(kPos);
			break;

		case 2:
			option2(kPos, &pathT);
			break;

		case 3:
			option3(kPos, &pathT, &posList);
			break;

		case 4:
			option4(kPos, &pathT, posList);
			break;

		case 5:
			option5();
			break;

		case 6:
			break;

		default:
			printf("Enter an option from the list above\n");
		}

	}

	if (posList == NULL)
		free(posList);
	else
		freeList(posList);

	freeTree(pathT);
	free(kPos);
	free(fileName);

	printf("Exiting\n");
}

void printMenu()
{
	printf("Main menu:\n");
	printf("1. Enter a knight's starting position\n");
	printf("2. Create all possible knight paths\n");
	printf("3. Find a knight path covering all board\n");
	printf("4. Save knight path covering all board to file\n");
	printf("5. Load and display path from file\n");
	printf("6. Exit\n");
}

int receiveOptionFromUser()
{
	int option;

	printf("\nPlease enter the number of your option\n");

	scanf("%d", &option);

	return option;
}

char* getFileName()
{
	int logSize = 0, phySize = 1;
	char currChar = 0;
	char* res;

	res = (char*)malloc(phySize * sizeof(char));
	checkMemoryFail(res);
	printf("Please enter file's name:\n");
	currChar = getchar();
	if (currChar = '\n')
		currChar = getchar();

	while (currChar != '\n')
	{
		if (logSize == phySize)
		{
			phySize = (phySize * 2) + 1;
			res = (char*)realloc(res, sizeof(char) * phySize);
			checkMemoryFail(res);
		}

		res[logSize] = currChar;
		logSize++;
		currChar = getchar();
	}

	res = (char*)realloc(res, sizeof(char) * (logSize + 1));
	checkMemoryFail(res);
	res[logSize] = '\0';
	return res;
}

void option1(chessPos* pos)
{
	char row, col;
	bool flag = true;

	while (flag)
	{
		printf("Please enter a position on the board, a char for the row (A - H) and a number for the col (1 - 8):\n");
		scanf(" %c%c", &row, &col);

		if ('A' <= row && row <= 'H' && '1' <= col && col <= '8')
			flag = FALSE;
	}

	(*pos)[0] = row;
	(*pos)[1] = col;
}

void option2(chessPos* kPos, pathTree* tree)
{
	if ((*kPos)[0] == '0' && (*kPos)[1] == '0')
		printf("Please enter first a knight's starting position (option 1)\n");
	else
	{
		*tree = findAllPossibleKnightPaths(kPos);
	}
}

void option3(chessPos* kPos, pathTree* pathT, chessPosList** posList)
{

	if ((*kPos)[0] == '0' && (*kPos)[1] == '0')
		printf("Please enter first a knight's starting position (option 1)\n");

	else
	{
		if (pathT->root == NULL)
			option2(kPos, pathT);

		*posList = findKnightPathCoveringAllBoard(pathT);

		if(*posList == NULL)
			printf("There is no path that covering all the board\n");
	}
}

void option4(chessPos* kPos, pathTree* pathT, chessPosList* posList)
{
	char* fileName;

	if ((*kPos)[0] == '0' && (*kPos)[1] == '0')
		printf("Please enter first a knight's starting position (option 1)\n");

	else
	{
		if (pathT->root == NULL)
			option2(kPos, pathT);

		if (posList == NULL)
			option3(kPos, pathT, &posList);

		if (posList == NULL)
		{
			printf("There is no path that covering all the board.\n");
			return;
		}

		fileName = getFileName();

		saveListToBinFile(fileName, posList);
	}
}

void option5()
{
	int res;
	char* fileName;
	
	fileName = getFileName();

	res = checkAndDisplayPathFromFile(fileName);

	switch (res)
	{
	case 1:
		printf("The list does not contain a valid path.\n");
		break;
	case 2:
		printf("The path covers all the board.\n");
		break;
	case 3:
		printf("The path does not cover all the board.\n");
		break;
	case -1:
		printf("The file does not exist.\n");
		break;
	}
}