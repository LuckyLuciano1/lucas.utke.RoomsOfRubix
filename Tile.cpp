#include "Tile.h"
Tile::Tile() {}

void Tile::Init(ALLEGRO_BITMAP *TileImage, double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY)
{
	Object::Init(x, y, z, TILEW, TILEH, imageX, imageY, imageboundX, imageboundY, x, y, TILEW, TILEH);

	SetVerticality(HORIZONTAL);
	SetAnimating(false);

	Object::image = TileImage;
	state = STABLE;
	MaxHeight = 3;
	Vel = 3;
	gradient = al_map_rgba_f(0, rand()%(255/16) + (255/16)*15, 0, .01);//temp
}

void Tile::Render(double cameraXPos, double cameraYPos)
{
	if (z != 0) {
		for (int a = 0; a > (z - boundY); a -= boundY) {
			if(a == -boundY)
				al_draw_tinted_scaled_rotated_bitmap_region(image, 0, 400, imageboundX, imageboundY, transparency, boundX / 2, boundY / 2, x + cameraXPos, y + z - a + cameraYPos, boundX / imageboundX, boundY / imageboundY, angle, FlipHorizontal);
			else
				al_draw_tinted_scaled_rotated_bitmap_region(image, 200, 400, imageboundX, imageboundY, transparency, boundX / 2, boundY / 2, x + cameraXPos, y + z - a + cameraYPos, boundX / imageboundX, boundY / imageboundY, angle, FlipHorizontal);

		}
		al_draw_tinted_scaled_rotated_bitmap_region(image, 400, 400, imageboundX, imageboundY, al_map_rgba_f(255 / 2, 255 / 2, 255 / 2, .7), boundX / 2, 0, x + cameraXPos, y + z + boundY - (boundY / 2) + cameraYPos, boundX / imageboundX, (boundY - z) / imageboundY, angle, FlipHorizontal);
	}

	Object::Render(cameraXPos, cameraYPos);
	//gradient above tile to vary terrain color
	al_draw_tinted_scaled_rotated_bitmap_region(image, 800, 0, imageboundX, imageboundY, gradient, (boundX - (boundX / 25)) / 2, (boundY - (boundY/25)) / 2, x + (boundX/(50))+cameraXPos, y + z+(boundY/(50)) + cameraYPos, (boundX - (boundX / 25)) / imageboundX, (boundY - (boundY/25)) / imageboundY, angle, FlipHorizontal);
}

void Tile::Update()
{
	/*if (state == STABLE) {
		if (rand() % 1000 == 1)
			state = RISING;
	}
	if (state == SINKING) {
		if (rand() % 1000 == 1)
			state = RISING;
	}
	if (state == RISING) {
		if (rand() % 1000 == 1)
			state = SINKING;
		if (rand() % 1000 == 1)
			state = STABLE;
	}*/


	if (state == SINKING)
		z +=  Vel;
	if (state == RISING)
		z -=  Vel;

	if ((state == SINKING) && z >= 0) {
		z = 0;
		state = STABLE;
	}
	if ((state == RISING) && z < boundY*-MaxHeight) {
		state = SINKING;
		MaxHeight = 2;//resets MaxHeight to original default.
	}



	Object::Update();
}