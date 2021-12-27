
#ifndef FINAL_PROJECT_GENERAL_H
#define FINAL_PROJECT_GENERAL_H

#include <stdio.h>
#include <stdlib.h>

/* Checks for memory allocation errors, exits if it happens. */
void checkMemoryFail(void *ptr);
/* Checks if file opened properly, exits if not. */
void checkFile(FILE* f);
#endif
