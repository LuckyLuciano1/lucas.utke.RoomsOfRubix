#include "Player.h"
#include "String.h"
#include "PlayerCloak.h"

#define PI 3.14159265
#define DEGREES(x) int((x)/360.0*0xFFFFFF)
#define RADIANS(x) int((x)/2/M_PI*0xFFFFFF)

Player::Player() {}

void Player::Init(double x, double y, double z)
{

	Object::Init(x, y, z);
	EnableSorting(25, 25);

	MouseAngleRadians = 0;//temporary value
	velX = 6;
	velY = 6;

	string->Init(x, y+z, 50, 1, 15, 15);//creating the scarf
	playercloakpiece1->Init(x - boundX/2, y+z, 150, 1, 150, 1, 81, 75, 69);
	playercloakpiece2->Init(x - (boundX / 2) - 10, y + z, 130, 1, 130, 1, 71, 65, 59);
	playercloakpiece3->Init(x - (boundX / 2) + 30, y + z, 130, 1, 130, 1, 71, 65, 59);
}

void Player::Update()
{
	Object::Update();
}

void Player::Render(double cameraXPos, double cameraYPos)
{
	//string->Update(x+boundX/2, y + z, dirX, dirY, cameraXPos, cameraYPos);
	
	//playercloakpiece3->Update(z, dirX, dirY, velX, velY, cameraXPos, cameraYPos);
	//playercloakpiece2->Update(z, dirX, dirY, velX, velY, cameraXPos, cameraYPos);
	//playercloakpiece1->Update(z, dirX, dirY, velX, velY, cameraXPos, cameraYPos);
	
	//Object::Render(cameraXPos, cameraYPos);
	al_draw_rectangle(x + cameraXPos, y + z + cameraYPos, x + cameraXPos + boundX, y + z + cameraYPos + boundY, al_map_rgb(255, 255, 255), 2);
	
	//al_draw_tinted_scaled_rotated_bitmap_region(image, 0, 0, 345, 239, al_map_rgba_f(1, 1, 1, 1), 0, 0, x + cameraXPos + boundX/2 - (345*.15)/2, y + z + cameraYPos, .15, .15, 0, 0);
}

void Player::PlayerKeyboard(bool UP, bool DOWN, bool LEFT, bool RIGHT, bool SHIFT)
{
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
		AnimationHandler();
	}
	else if (RIGHT) {
		Action = MOVING;
		dirX = 1;
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

	}
	else if (Action == MOVING) {

	}
	else if (Action == CHARGE) {

	}
}