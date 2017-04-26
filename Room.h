#pragma once

#include <iostream>
#include "Globals.h"
#include "Object.h"
#include "Player.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>

using namespace std;

class Room
{
protected:
	char ID;//means of identifying what room it is. will be every letter in the alphabet, plus '_' (27 rooms, 26 letters).

	int x;//coordinate of room in 3D matrix. Used to identify what room should be connected what.
	int y;
	int z;
	
	char XAdj;//tracks what other rooms this room is linked to (via ID). '/' mark means it is next to nothing on that plane.
	char NegXAdj;
	char YAdj;
	char NegYAdj; 
	char ZAdj;
	char NegZAdj;

	vector<Object*> ObjectList;//list that keeps track of all objects within each room. Used for render, updating, collision, etc.
	vector<Object*>::iterator iter;

	vector<Object *> ObjectCollisionList;//list that keeps track of all objects that must collide with each other. 
	vector<Object*>::iterator citer;
	vector<Object*>::iterator citer2;

	//level map. randomly generated within Init().
	int LevelMatrix[LEVELW][LEVELH];

public:

	Room();
	void virtual Destroy();
	void Init(char ID, int x, int y, int z, Player *player, ALLEGRO_BITMAP *TerrainImage);

	char GetID() { return ID; }
	void SetID(char ID) { Room::ID = ID; }

	int GetX() { return x; }
	int GetY() { return y; }
	int GetZ() { return z; }

	void SetX(int x) { Room::x = x; }
	void SetY(int y) { Room::y = y; }
	void SetZ(int z) { Room::z = z; }

	//==============================================
	//OBJECT LIST MANAGEMENT
	//==============================================
	void ObjectUpdate(int CameraXDir, int CameraYDir);
	void ObjectRender();
	void ObjectCollision();
	void ObjectDeletion();

	//bool compare(Object *L1, Object *L2);//sorts ObjectList based on y position (isometric view of sorts)

	//==============================================
	//ADJACENT ROOM ACCESS/MODIFICATION
	//==============================================
	char GetXAdj() { return XAdj; }
	char GetNegXAdj() { return NegXAdj; }
	char GetYAdj() { return YAdj; }
	char GetNegYAdj() { return NegYAdj; }
	char GetZAdj() { return ZAdj; }
	char GetNegZAdj() { return NegZAdj; }

	void SetXAdj(char XAdj) { Room::XAdj = XAdj; }
	void SetNegXAdj(char NegXAdj) { Room::NegXAdj = NegXAdj; }
	void SetYAdj(char YAdj) { Room::YAdj = YAdj; }
	void SetNegYAdj(char NegYAdj) { Room::NegYAdj = NegYAdj; }
	void SetZAdj(char Zadj) { Room::ZAdj = ZAdj; }
	void SetNegZAdj(char NegZadj) { Room::NegZAdj = NegZAdj; }
	//==============================================
	//SHUFFLING GUIDELINES
	//==============================================
	void Shuffle(int shuffletype);

	void RedClockwise();
	void RedCounterClockwise();

	void WhiteClockwise();
	void WhiteCounterClockwise();

	void BlueClockwise();
	void BlueCounterClockwise();
	
	void YellowClockwise();
	void YellowCounterClockwise();

	void GreenClockwise();
	void GreenCounterClockwise();

	void OrangeClockwise();
	void OrangeCounterClockwise();
};