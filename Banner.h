#pragma once

#include <iostream>
#include "Globals.h"
#include "Object.h"
#include "String.h"
#include <vector>
using namespace std;

class Banner : public Object
{
private:
	String *string = new String();
public:
	Banner();
	void Init(ALLEGRO_BITMAP *BannerImage, double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY);
	void Render(double cameraXPos, double cameraYPos);
	void Update();
};
