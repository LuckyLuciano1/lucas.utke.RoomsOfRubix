#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class CloudStrip : public Object
{
private:
	int R;//color of base
	int G;
	int B;

	vector<Object*> AllObjectsList;
	vector<Object*>::iterator iter;

public:
	CloudStrip();
	void Init(double y, double z, double boundX, int RadiusRange, int RadiusMin, int R, int G, int B);
	void Update();
	void Render(double cameraXPos, double cameraYPos);
};