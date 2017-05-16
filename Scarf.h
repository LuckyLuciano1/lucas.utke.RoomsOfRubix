#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class Scarf : public Object
{
private:
	int ScarfPieceNum;
	int ScarfPieceSpacing;
public:
	Scarf();
	 void Init(double x, double y, double z, int ScarfPieceNum);
	 void Update();
};