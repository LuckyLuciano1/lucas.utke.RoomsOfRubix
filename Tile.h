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
public:
	Tile();
	void Init(ALLEGRO_BITMAP *TileImage, double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY);
	void Render(double cameraXPos, double cameraYPos);
	void Update();

	int GetState() { return state; }
	void SetState(int state) { Tile::state = state; }
};