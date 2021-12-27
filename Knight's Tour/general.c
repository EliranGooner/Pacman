#include "general.h"
void checkMemoryFail(void *ptr)
{
    if (ptr == NULL)
    {
        printf("Memory allocation error! Exiting!");
        exit(1);
    }
}

/* Check if the file was opened correctly */
void checkFile(FILE* f)
{
	if (f == NULL)
	{
		printf("Failed opening the file, Exiting!");
		exit(1);
	}
}