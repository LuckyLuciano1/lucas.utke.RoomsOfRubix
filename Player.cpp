#include "Player.h"
#define PI 3.14159265
#define DEGREES(x) int((x)/360.0*0xFFFFFF)
#define RADIANS(x) int((x)/2/M_PI*0xFFFFFF)

Player::Player() {}

void Player::Init(double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY, ALLEGRO_BITMAP *PlayerImage)
{
	Object::Init(x, y, z, imageboundX / 2, imageboundY / 2, imageX, imageY, imageboundX, imageboundY, x, y, 30, 90);

	Object::image = PlayerImage;

	MouseAngleRadians = 0;//temporary value
	velX = 6;
	velY = 6;
}

void Player::Update(double cameraXDir, double cameraYDir)
{
	Object::Update(cameraXDir, cameraYDir);
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
/*
//updating angle of playerspear
if (playerspear->GetSpearState() == 2) {//idle state
	playerspear->SetAngle(atan2(mousey - (player->GetY() + player->GetBoundY() / 2), mousex - (player->GetX() + player->GetBoundX() / 2)) - sqrt(2) / 2);
}
//updating player angle
player->SetMouseAngleRadians(P_M_AngleRadians);

//player movement/attacks
if (PlayerLunge == true) {//lunge, only true when Mouse Button is released

	player->Lunge(StoredP_M_AngleRadians);

	if (player->GetLungeTime() >= 20) {//runs at beginning of lunge
		playerspear->SetSpearState(1);//lunging state
		playerspear->SetAngle(atan2(mousey - (player->GetY() + player->GetBoundY() / 2), mousex - (player->GetX() + player->GetBoundX() / 2)) - sqrt(2) / 2);
	}
	else if (player->GetLungeTime() <= 0) {//runs at end of lunge
		PlayerLunge = false;
		player->ResetAnimation(0);
		player->ResetAnimation(1);
	}
}
else if (keys[MOUSE_BUTTON]) {//charging

	if (player->GetChargeTime() == 0) {//runs at beginning of charge

		player->SetChargeTime(10);//begins with small ChargeTime to make some flame regardless of amount charged
		player->SetLungeTime(21);//setup for later lunge
	}
	if (player->GetChargeTime() == 20) {//runs when into  charge (1/3 sec)
		playerspear->SetSpearState(0);//spinning state. delayed slightly to allow for fast without making the spear twitch.

		player->SetDirX(0);//makes player stationary
		player->SetDirY(0);//delayed slightly for aesthetic purposes (no mathematic or structural reason).
	}
	playerspear->SetChargeTime(player->GetChargeTime());
	StoredP_M_AngleRadians = P_M_AngleRadians;

	player->Charge(mousex);
}
else {//basic movement

	player->SetChargeTime(0);//chargeTime set to 0
	playerspear->SetChargeTime(0);
	playerspear->SetSpearState(2);//idle state

	if (keys[UP]) {//player movement
		player->MoveUp();
	}
	else if (keys[DOWN]) {
		player->MoveDown();
	}
	else {
		player->ResetAnimation(1);
	}

	if (keys[LEFT]) {
		player->MoveLeft();
	}
	else if (keys[RIGHT]) {
		player->MoveRight();
	}
	else {
		player->ResetAnimation(0);
	}
}*/