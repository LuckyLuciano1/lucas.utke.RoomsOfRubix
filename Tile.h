#pragma once

#include <iostream>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class Tile : public Object
{
public:
	Tile();
	void Init(ALLEGRO_BITMAP *TileImage, double x, double y, double z, int imageX, int imageY, int imageboundX, int imageboundY);
	void Render();
	void Update(double cameraX, double cameraY);
};