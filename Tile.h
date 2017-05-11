#pragma once

#include <iostream>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class Tile : public Object
{
private:
	enum STATE {
	SINKING,
	RISING,
	STABLE
	};
	int state;
	int MaxHeight;//multiply with BoundY and -1 to get actual value change
	int Vel;

	ALLEGRO_COLOR gradient;//temp
public:
	Tile();
	void Init(ALLEGRO_BITMAP *TileImage, int layer, double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY);
	void Render(double cameraXPos, double cameraYPos);
	void Update();

	int GetState() { return state; }
	void SetState(int state) { Tile::state = state; }
	
	int GetVel() { return Vel; }
	void SetVel(int Vel) { Tile::Vel = Vel; }

	void RiseTo(int MaxHeight) { Tile::MaxHeight = MaxHeight, Tile::state = RISING; }

};