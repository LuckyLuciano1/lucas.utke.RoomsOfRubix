#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class ScarfPiece : public Scarf
{
private:
	double ObjX;//area that object is moving towards
	double ObjY;
	double ObjZ;
public:
	ScarfPiece();
	void Init(double Objx, double Objy, double Objz);
	void Update(double dirX, double dirY, double dirZ);
};