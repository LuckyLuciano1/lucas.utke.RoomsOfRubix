#include "DecorBox.h"

DecorBox::DecorBox() {}//DecorBox is an object with no collision that renders a simple box

void DecorBox::Init(double x, double y, double z, double boundX, double boundY, int R, int G, int B)
{
	Object::Init(x, y, z, boundX, boundY, 0, 0, 0, 0, 0, 0, 0, 0);

	DecorBox::R = R;//color of box
	DecorBox::G = G;
	DecorBox::B = B;
}

void DecorBox::Update()
{
	Object::Update();
}

void DecorBox::Render(double cameraXPos, double cameraYPos)
{
	al_draw_filled_rectangle(x + cameraXPos, y + cameraYPos + z, x + boundX + cameraXPos, y + boundY + cameraYPos + z, al_map_rgb(R, G, B));//base
}