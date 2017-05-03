#include "Tile.h"
Tile::Tile() {}

void Tile::Init(ALLEGRO_BITMAP *TileImage, double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY) 
{
	Object::Init(x, y, z, TILEW, TILEH, imageX, imageY, imageboundX, imageboundY, x, y, TILEW, TILEH);

	SetAnimating(false);	
	Object::image = TileImage;
	state = STABLE;
}

void Tile::Render(double cameraXPos, double cameraYPos)
{
	if (state != STABLE) {
		for (int a = 0; a > (z - boundY); a -= boundY) {
			al_draw_tinted_scaled_rotated_bitmap_region(image, 0, 200, imageboundX, imageboundY, transparency, boundX / 2, boundY / 2, x + cameraXPos, y + z - a + cameraYPos, boundX / imageboundX, boundY / imageboundY, angle, FlipHorizontal);
		}
		al_draw_tinted_scaled_rotated_bitmap_region(image, 200, 200, imageboundX, imageboundY, al_map_rgba_f(255 / 2, 255 / 2, 255 / 2, .5), boundX / 2, 0, x + cameraXPos, y + z + boundY - (boundY/2) + cameraYPos, boundX / imageboundX, (boundY - z) / imageboundY, angle, FlipHorizontal);
	}

	Object::Render(cameraXPos, cameraYPos);
}

void Tile::Update()
{
		/*if (state == STABLE) {
			if (rand() % 10000 == 1)
				state = RISING;
		}
		if (state == SINKING) {
			if (rand() % 10000 == 1)
				state = RISING;
		}
		if (state == RISING) {
			if (rand() % 10000 == 1)
				state = SINKING;
		}*/

		if ((state == SINKING) && z == 0)
			state = STABLE;
		if ((state == RISING) && z < boundY*-1)
			state = SINKING;
	

		if (state == SINKING)
			z+=2;
		else if (state == RISING)
			z-=2;

	Object::Update();
}