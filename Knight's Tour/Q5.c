#include "Q5.h"

void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	FILE* f;
	short int size;
	int numOfBytes;
	chessPosCell* head = pos_list->head;

	f = fopen(file_name , "wb");
	checkFile(f);

	size = (short int)sizeOfLst(pos_list);

	fwrite(&size, sizeof(short int), 1, f);

	numOfBytes = numberOfBytes(size);

	BYTE* binArr = (BYTE*)calloc(numOfBytes, sizeof(BYTE));
	checkMemoryFail(binArr);

	insertPosToBinArr(binArr, head);

	fwrite(binArr, sizeof(BYTE), numOfBytes, f);

	free(binArr);

	fclose(f);
}


BYTE charToByte(char ch)
{
	BYTE byte;
	byte = ch - 'A';

	return byte;
}


BYTE numToByte(char ch)
{
	BYTE byte;
	byte = ch - '0' - 1;
	
	return byte;
}


int numberOfBytes(short size)
{
	int num = size * 6;

	if (num % 8 == 0)
		return (int)(num/8);
	else
		return (int)(num/8 + 1);
}


void insertPosToBinArr(BYTE* binArr, chessPosCell* head)
{
	chessPosCell* curr = head;
	int i=0, countBit = 0, spaceLeft;
	BYTE row, col, mask;

	while (curr != NULL)
	{
		row = charToByte(curr->position[0]);
		col = numToByte(curr->position[1]);

		spaceLeft = byteSIZE - countBit;

		spaceOptions(binArr, &i, &countBit, &spaceLeft, row);

		if (countBit == 0)
		{
			mask = row << 7;

			binArr[i] |= mask;
			countBit += 1;
			spaceLeft = byteSIZE - countBit;
		}

		spaceOptions(binArr, &i, &countBit, &spaceLeft, col);

		if (countBit == 0)
		{
			mask = col << 6;

			binArr[i] |= mask;
			countBit += 2;
			spaceLeft = byteSIZE - countBit;
		}

		if (spaceLeft == 0)
		{
			countBit = 0;
			i++;
		}

		curr = curr->next;
	}
}


void spaceOptions(BYTE* binArr, int* i,int* countBit, int* spaceLeft, BYTE posByte)
{
	BYTE mask;
	int space = *spaceLeft;
	int j = *i;

	if (space >= 3)
	{
		mask = posByte << (space - 3);
		binArr[j] |= mask;
		
		*countBit += 3;
		*spaceLeft = byteSIZE - *countBit;
	}
	else if (space == 2)
	{
		mask = posByte >> 1;
		binArr[j] |= mask;
		*i += 1;
		*countBit = 0;
	}
	else if (space == 1)
	{
		mask = posByte >> 2;
		binArr[j] |= mask;
		*i += 1;
		*countBit = 0;
	}
}