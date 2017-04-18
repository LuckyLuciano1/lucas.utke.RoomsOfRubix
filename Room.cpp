#include "Room.h"
#include <math.h>
#include <iostream>
using namespace std;

Room::Room()
{
	ID = 0;

	x = 0;
	y = 0;
	z = 0;
}

void Room::Destroy() {}

void Room::Init(char ID, int x, int y, int z)
{
	Room::ID = ID;
	Room::x = x;
	Room::y = y;
	Room::z = z;

	LevelMatrix[LEVELW][LEVELH] = {};

	for (int x = 0; x < LEVELW; x++) {
		for (int y = 0; y < LEVELH; y++) {
			if (rand() % 2 == 1)
				LevelMatrix[x][y] = 1;
			else
				LevelMatrix[x][y] = 0;
		}
	}
}