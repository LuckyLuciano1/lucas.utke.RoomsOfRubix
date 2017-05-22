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
	//gradient = al_map_rgb(100, 130, 80);//temp
}

void Tile::Render(double cameraXPos, double cameraYPos)
{
	if (z != 0) {
		for (int a = 0; a > (z - boundY); a -= boundY - 1) {
			if (a == -boundY + 1) {
				al_draw_tinted_scaled_rotated_bitmap_region(image, 0, 400, imageboundX, imageboundY, transparency, 0, 0, x + cameraXPos, y + z - a + cameraYPos, boundX / imageboundX, boundY / imageboundY, angle, FlipHorizontal);
				//al_draw_filled_rectangle((x + cameraXPos), (y + cameraYPos + z - a), (x + boundX + cameraXPos), (y + boundY + cameraYPos + z - a), al_map_rgb(128, 128, 128));
			}
			else {
				al_draw_tinted_scaled_rotated_bitmap_region(image, 200, 400, imageboundX, imageboundY, transparency, 0, 0, x + cameraXPos, y + z - a + cameraYPos, boundX / imageboundX, boundY / imageboundY, angle, FlipHorizontal);
				//al_draw_filled_rectangle((x + cameraXPos), (y + cameraYPos + z - a), (x + boundX + cameraXPos), (y + boundY + cameraYPos + z - a), al_map_rgb(128, 128, 128));
			}
		}
		al_draw_tinted_scaled_rotated_bitmap_region(image, 400, 400, imageboundX, imageboundY, al_map_rgba_f(255 / 2, 255 / 2, 255 / 2, .7), 0, 0, x + cameraXPos, y + z + boundY - (boundY / 2) + cameraYPos, boundX / imageboundX, (boundY - z) / imageboundY, angle, FlipHorizontal);
	}

	//al_draw_filled_rectangle((x + cameraXPos), (y + cameraYPos + z), (x + boundX + cameraXPos), (y + boundY + cameraYPos + z), al_map_rgb(100, 109, 71));
	//al_draw_filled_rectangle((x + cameraXPos + (boundX/15)), (y + cameraYPos + (boundY / 15) + z), (x + boundX + cameraXPos - (boundX/30)), (y + boundY + cameraYPos - (boundY / 30) + z), gradient);
	
	//gradient above tile to vary terrain color
	
	//al_draw_tinted_scaled_rotated_bitmap_region(image, imageX, imageY, imageboundX, imageboundY, transparency, 0, 0, x + cameraXPos, y + z + cameraYPos, boundX / imageboundX, boundY / imageboundY, angle, FlipHorizontal);//scaling seems incorrect
	Object::Render(cameraXPos, cameraYPos);
	al_draw_tinted_scaled_rotated_bitmap_region(image, 800, 0, imageboundX, imageboundY, gradient, 0, 0, x + (boundX/(50))+cameraXPos, y + z+(boundY/(50)) + cameraYPos, (boundX - (boundX / 25)) / imageboundX, (boundY - (boundY/25)) / imageboundY, angle, FlipHorizontal);
	//al_draw_rectangle(x + cameraXPos, y + z + cameraYPos, x + cameraXPos + TILEW, y + cameraYPos + TILEH, al_map_rgb(0, 255, 0), 3);
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