#include "Object.h"
#include <math.h>
#include <iostream>
using namespace std;

Object::Object()
{
	valid = true;

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
	transparency = al_map_rgba_f(1, 1, 1, 1);

	boundX = 0;
	boundY = 0;

	imageX = 0;
	imageY = 0;
	imageboundX = 0;
	imageboundY = 0;

	colX = 0;
	colY = 0;
	colboundX = 0;
	colboundY = 0;

	maxFrame = 0;
	curFrame = 0;

	maxRow = 0;
	curRow = 0;

	image = NULL;
	//collidable = false;
}

void Object::Destroy() {}

void Object::Init(double x, double y, double z, int boundX, int boundY, int imageX, int imageY, int imageboundX, int imageboundY, int colX, int colY, int colboundX, int colboundY)
{
	Object::x = x;
	Object::y = y;
	Object::z = z;

	Object::boundX = boundX;
	Object::boundY = boundY;

	Object::imageX = imageX;
	Object::imageY = imageY;
	Object::imageboundX = imageboundX;
	Object::imageboundY = imageboundY;

	Object::colX = colX;
	Object::colY = colY;
	Object::colboundX = colboundX;
	Object::colboundY = colboundY;
}

void Object::Update(double cameraX, double cameraY) 
{	
	x += velX*dirX;
	y += velY*dirY;
	z += velZ*dirZ;

	x += cameraX;
	y += cameraY;
	//no camera update for z because it eventually gets added into y, and is not an actual dimension within the parameters of the game.

	colX += velX*dirX;
	colY += velY*dirY;
	if (animating) {
		if (curFrame < maxFrame)//creates movement of frames
			curFrame++;
		else
			curFrame = 0;
	}

	/*if (x > cameraX &&//sets collision to false when outside of frame
		x + boundX < cameraX + SCREENW &&
		y > cameraY &&
		y + boundY > cameraY + SCREENH)
		collidable = true;
	else
		collidable = false;*/
}

void Object::Render()
{
	al_draw_tinted_scaled_rotated_bitmap_region(image, imageX, imageY, imageboundX, imageboundY, transparency, boundX/2, boundY/2, x, y + z, boundX/imageboundX, boundY/imageboundY, angle, 0);
	//cumulative drawing function that should be able to handle all possible drawing commands.
}

bool Object::CollisionCheck(Object *otherObject) {
	collision = false;
	double oX = otherObject->GetColX();
	double oY = otherObject->GetColY();

	int obX = otherObject->GetColBoundX();
	int obY = otherObject->GetColBoundY();

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