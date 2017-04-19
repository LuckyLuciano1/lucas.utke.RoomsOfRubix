#include "Object.h"
#include <math.h>
#include <iostream>
using namespace std;

Object::Object()
{
	x = 0;
	y = 0;
	z = 0;

	velX = 1;
	velY = 1;
	velZ = 1;

	dirX = 0;
	dirY = 0;
	dirZ = 0;

	angle = 0;

	boundX = 0;
	boundY = 0;

	imageX = 0;
	imageY = 0;
	imageboundX = 0;
	imageboundY = 0;

	maxFrame = 0;
	curFrame = 0;

	maxRow = 0;
	curRow = 0;

	image = NULL;
	collidable = false;
}

void Object::Destroy() {}

void Object::Init(double x, double y, double z) 
{
	Object::x = x;
	Object::y = y;
	Object::z = z;
}

void Object::Update(double cameraX, double cameraY) 
{	
	x += velX*dirX;
	y += velY*dirY;
	z += velZ*dirZ;

	x += cameraX;
	y += cameraY;
	//no camera update for z because it eventually gets added into y, and is not an actual dimension within the parameters of the game.

	if (curFrame<maxFrame)
		curFrame++;
	else
		curFrame = 0;

	if (x > cameraX &&
		x + boundX < cameraX + SCREENW &&
		y > cameraY &&
		y + boundY > cameraY + SCREENH)
		collidable = true;
	else
		collidable = false;
}

void Object::Render()
{
	al_draw_tinted_scaled_rotated_bitmap_region(image, imageX, imageY, imageboundX, imageboundY, al_map_rgba_f(1, 1, 1, 1), boundX/2, boundY/2, x, y + z, imageboundX/boundX, imageboundY/boundY, angle, 0);
	//cumulative drawing function that should be able to handle all possible drawing commands.
}

bool Object::CollisionCheck(Object *otherObject) {
	collision = false;
	double oX = otherObject->GetX();
	double oY = otherObject->GetY();

	int obX = otherObject->GetBoundX();
	int obY = otherObject->GetBoundY();

	double onewX = (otherObject->GetVelX()*otherObject->GetDirX());
	double onewY = (otherObject->GetVelY()*otherObject->GetDirY());

	double newX = velX *dirX;
	double newY = velY *dirY;

	if (x + boundX + newX > oX + onewX &&
		x + newX < oX + obX + onewX &&
		y + boundY + newY > oY + onewY &&
		y + newY < oY + obY + onewY)
		return true;
	else
		return false;
}

void Object::Collided(Object *otherObject) 
{
	collision = true;
}