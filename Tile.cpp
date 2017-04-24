#include "Tile.h"
Tile::Tile() {}

void Tile::Init(double x, double y, double z, int imageX, int imageY, int imageboundX, int imageboundY) 
{
	Object::Init(x, y, z);
	boundX = TILEW;
	boundY = TILEH;

	Object::imageX = imageX;
	Object::imageY = imageY;
	Object::imageboundX = imageboundX;
	Object::imageboundY = imageboundY;

	Object::image = al_load_bitmap("TerrainImage.png");//currently does not like 'image' (any al command involving 'image' will crash the program).

	if (Object::image == NULL)
		cout <<" IT'S NULL" << endl;//it is for some reason

	//al_convert_mask_to_alpha(image, al_map_rgb(255, 255, 255));
}

void Tile::Render()
{
	Object::Render();
}

void Tile::Update(double cameraX, double cameraY)
{
	Object::Update(cameraX, cameraY);
}