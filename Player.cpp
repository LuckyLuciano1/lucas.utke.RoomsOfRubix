#include "Player.h"
#define PI 3.14159265
#define DEGREES(x) int((x)/360.0*0xFFFFFF)
#define RADIANS(x) int((x)/2/M_PI*0xFFFFFF)

Player::Player() {}

void Player::Init(double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY, ALLEGRO_BITMAP *PlayerImage)
{
	Object::Init(x, y, z, imageboundX/2, imageboundY/2, imageX, imageY, imageboundX, imageboundY, x, y, 30, 90);

	Object::image = PlayerImage;

	MouseAngleRadians = 0;//temporary value
}

void Player::Update(double cameraXDir, double cameraYDir)
{
	Object::Update(cameraXDir, cameraYDir);
}

void Player::MoveUp() {
	if (MouseAngleRadians > 3 * PI / 2 ||//animation is based on position of mouse, so that it better aligns with spear direction
		MouseAngleRadians < PI / 2) {
		Animation = MOVING;
		FlipHorizontal = true;
	}
	else {
		Animation = MOVING;
		FlipHorizontal = false;
	}
	dirY = -1;
	AnimationHandler();
}
void Player::MoveDown() {
	if (MouseAngleRadians > 3 * PI / 2 ||//animation is based on position of mouse, so that it better aligns with spear direction
		MouseAngleRadians < PI / 2) {
		Animation = MOVING;
		FlipHorizontal = true;
	}
	else {
		Animation = MOVING;
		FlipHorizontal = false;
	}
	dirY = 1;
	AnimationHandler();
}
void Player::MoveLeft() {
	if (MouseAngleRadians > 3 * PI / 2 ||//animation is based on position of mouse, so that it better aligns with spear direction
		MouseAngleRadians < PI / 2) {
		Animation = MOVING;
		FlipHorizontal = true;
	}
	else {
		Animation = MOVING;
		FlipHorizontal = false;
	}
	dirX = -1;
	AnimationHandler();
}
void Player::MoveRight() {
	if (MouseAngleRadians > 3 * PI / 2 ||//animation is based on position of mouse, so that it better aligns with spear direction
		MouseAngleRadians < PI / 2) {
		Animation = MOVING;
		FlipHorizontal = true;
	}
	else {
		Animation = MOVING;
		FlipHorizontal = false;
	}
	dirX = 1;
	AnimationHandler();
}

void Player::ResetAnimation(int position)
{
	if (position == 1) {
		if (Animation == MOVING || Animation == IDLE || Animation == DASH) {
			if (MouseAngleRadians > 3 * PI / 2 ||
				MouseAngleRadians < PI / 2) {
				Animation = IDLE;
				FlipHorizontal = true;
			}
			else {
				Animation = IDLE;
				FlipHorizontal = false;
			}
		}
		else if (Animation == LUNGE || Animation == LUNGE) {
			if (MouseAngleRadians > 3 * PI / 2 ||
				MouseAngleRadians < PI / 2) {
				Animation = CHARGE;
				FlipHorizontal = true;
			}
			else {
				Animation = CHARGE;
				FlipHorizontal = false;
			}
		}

		dirY = 0;
		AnimationHandler();
	}
	else {
		dirX = 0;
		//AnimationHandler();
	}
}

//sets up the various variables that come alongside the Animation states. called whenever Animation is changed
void Player::AnimationHandler()
{
	//dimensions and other variables will default to:
	imageboundX = 39;
	imageboundY = 96;
	boundX = 39;
	boundY = 96;

	if (Animation == IDLE) {
		curRow = 0;
		maxFrame = 4;
	}
	else if (Animation == MOVING) {
		curRow = 1;
		maxFrame = 4;
	}
	else if (Animation == CHARGE) {
		curRow = 2;
		maxFrame = 1;
	}
	//sets curFrame based on maxFrame (otherwise, player will temporary disappear when it renders a position that is now greater than maxFrame)
	if (curFrame >= maxFrame) {
		curFrame = 0;
	}
}