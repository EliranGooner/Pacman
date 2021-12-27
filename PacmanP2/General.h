#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <queue>


// Moves cursor to x,y coordinate.
void gotoxy(int x, int y);
char randDirection();
void setColour(int colour);

// Current location and distance for shortest path algorithm
struct QItem {
	int row;
	int col;
	int dist;
	QItem(int x, int y, int w) : row(x), col(y), dist(w) {}
};
