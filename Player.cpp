#include "Player.h"

Player::Player() {}

void Player::Init(double x, double y, double z, int imageX, int imageY, int imageboundX, int imageboundY)
{
	Object::Init(x, y, z);
	boundX = TILEW;
	boundY = TILEH;

	Object::imageX = imageX;
	Object::imageY = imageY;
	Object::imageboundX = imageboundX;
	Object::imageboundY = imageboundY;
	Object::image = al_load_bitmap("PlayerImage.png");
	//al_convert_mask_to_alpha(image, al_map_rgb(255, 255, 255));
}