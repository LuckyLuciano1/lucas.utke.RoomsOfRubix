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
}