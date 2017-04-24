#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class Player : public Object
{
private:
public:
	Player();
	void Init(double x, double y, double z, int imageX, int imageY, int imageboundX, int imageboundY);
};