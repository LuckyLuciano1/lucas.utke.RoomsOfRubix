#pragma once

#include <iostream>
#include "Globals.h"
#include "Object.h"
#include <vector>

using namespace std;

class Room
{
protected:
	char ID;//means of identifying what room it is. will be every letter in the alphabet, plus one (27 rooms, 26 letters).

	int x;//coordinate of room in 3D matrix. Used to identify what room should be connected what.
	int y;
	int z;

	//proto
	vector<Object*> ObjectList;
	vector<Object*>::iterator iter;

	//level map. randomly generated within Init().
	int LevelMatrix[LEVELW][LEVELH];

public:

	Room();
	void virtual Destroy();
	void Init(char ID, int x, int y, int z);

	char GetID() { return ID; }
	void SetID(char ID) { Room::ID = ID; }

	int GetX() { return x; }
	int GetY() { return y; }
	int GetZ() { return z; }

	void SetX(int x) { Room::x = x; }
	void SetY(int y) { Room::y = y; }
	void SetZ(int z) { Room::z = z; }
};