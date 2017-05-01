#pragma once

#include <iostream>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class Tile : public Object
{
private:
	int zdest;//temp
public:
	Tile();
	void Init(ALLEGRO_BITMAP *TileImage, double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY);
	void Render();
	void Update(double cameraX, double cameraY);
};