#include "Tile.h"
Tile::Tile() {}

void Tile::Init(ALLEGRO_BITMAP *TileImage, double x, double y, double z, int imageX, int imageY, int imageboundX, int imageboundY) 
{
	Object::Init(x, y, z, TILEW, TILEH, imageX, imageY, imageboundX, imageboundY, x, y, TILEW, TILEH);

	SetAnimating(false);

	Object::image = TileImage;// al_load_bitmap("TerrainImage.png");//currently does not like 'image' (any allegro command involving 'image' will crash the program).
	//Object::image = al_load_bitmap("TerrainImage.png");
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