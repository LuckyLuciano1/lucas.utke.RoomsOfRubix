#include "Player.h"
#include "Scarf.h"
#define PI 3.14159265
#define DEGREES(x) int((x)/360.0*0xFFFFFF)
#define RADIANS(x) int((x)/2/M_PI*0xFFFFFF)

Player::Player() {}

void Player::Init(double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY, ALLEGRO_BITMAP *PlayerImage)
{
	
	Object::Init(x, y, z, imageboundX / 2.5, imageboundY / 2.5, imageX, imageY, imageboundX, imageboundY, x, y, imageboundX / 2.5, imageboundY / 2.5);
	Object::imageboundX = 193;
	Object::imageboundY = 361;
	Object::image = PlayerImage;

	MouseAngleRadians = 0;//temporary value
	velX = 6;
	velY = 6;

	scarf->Init(x, y, 20, 5);//creating the scarf
}

void Player::Update()
{
	//scarf->Update(x, y+z);
	Object::Update();
}

void Player::Render(double cameraXPos, double cameraYPos)
{
	scarf->Update(x + cameraXPos, y + z + cameraYPos);
	Object::Render(cameraXPos, cameraYPos);
}

void Player::PlayerKeyboard(bool UP, bool DOWN, bool LEFT, bool RIGHT, bool SHIFT)
{
	/*if (MouseAngleRadians > 3 * PI / 2 ||//determine direction player is facing based on mouse angle
		MouseAngleRadians < PI / 2) {
		FlipHorizontal = false;
	}
	else {
		FlipHorizontal = true;
	}*/

	if (UP) {//player movement
		Action = MOVING;
		dirY = -1;
		AnimationHandler();
	}
	else if (DOWN) {
		Action = MOVING;
		dirY = 1;
		AnimationHandler();
	}
	else {
		Action = IDLE;
		dirY = 0;
		AnimationHandler();
	}

	if (LEFT) {
		Action = MOVING;
		dirX = -1;
		FlipHorizontal = true;
		AnimationHandler();
	}
	else if (RIGHT) {
		Action = MOVING;
		dirX = 1;
		FlipHorizontal = false;
		AnimationHandler();
	}
	else {
		Action = IDLE;
		dirX = 0;
		AnimationHandler();
	}
}

//sets up the various variables that come alongside the Actionstates. called whenever Action is changed
void Player::AnimationHandler()
{
	if (Action == IDLE) {
		curRow = 0;
		maxFrame = 3;
	}
	else if (Action == MOVING) {
		curRow = 1;
		maxFrame = 3;
	}
	else if (Action == CHARGE) {
		curRow = 2;
		maxFrame = 3;
	}
	//sets curFrame based on maxFrame (otherwise, player will temporary disappear when it renders a position that is now greater than maxFrame)
	if (curFrame >= maxFrame) {
		curFrame = 0;
	}
}