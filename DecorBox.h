#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class DecorBox : public Object
{
private:
	int R;//color of base
	int G;
	int B;

public:
	DecorBox();
	void Init(double x, double y, double z, double boundX, double boundY, int R, int G, int B);
	void Update();
	void Render(double cameraXPos, double cameraYPos);
};