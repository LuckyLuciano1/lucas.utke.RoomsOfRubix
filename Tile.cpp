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
	//for (int a = 0; a < (z / boundY); a++) {
		al_draw_tinted_scaled_rotated_bitmap_region(image, 0, 200, imageboundX, imageboundY, transparency, boundX / 2, boundY / 2, x, y + z + 50, boundX / imageboundX, boundY / imageboundY, angle, FlipHorizontal);
		//al_draw_tinted_scaled_rotated_bitmap_region(image, 200, 200, imageboundX, imageboundY, al_map_rgba_f(0, 0, 0, .5), boundX / 2, boundY / 2, x, y + z + (a*boundY), boundX / imageboundX, boundY / imageboundY, angle, FlipHorizontal);
	//}
	Object::Render();
	
	//al_draw_textf(font18, al_map_rgb(255, 255, 255), 5, 5, 0, "ROOM: %c", CurrentRoom);
	
}

void Tile::Update(double cameraX, double cameraY)
{
	if (z > zdest)
		z--;
	else if (z < zdest)
		z++;
	else
		zdest = rand() % TILEH*3;
	Object::Update(cameraX, cameraY);
}