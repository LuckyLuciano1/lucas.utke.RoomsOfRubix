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
	image = al_load_bitmap("TerrainImage.png");
}