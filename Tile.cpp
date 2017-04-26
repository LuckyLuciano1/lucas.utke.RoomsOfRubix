#include "Tile.h"
Tile::Tile() {}

void Tile::Init(ALLEGRO_BITMAP *TileImage, double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY) 
{
	Object::Init(x, y, z, TILEW, TILEH, imageX, imageY, imageboundX, imageboundY, x, y, TILEW, TILEH);

	SetAnimating(false);
	
	Object::image = TileImage;
}

void Tile::Render()
{
	Object::Render();
}

void Tile::Update(double cameraX, double cameraY)
{
	Object::Update(cameraX, cameraY);
}