#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include "String.h"
#include <vector>
using namespace std;

class Player : public Object
{
private:
	enum ACTION {
		IDLE,
		MOVING,
		DASH,
		CHARGE,
		LUNGE
	};//list of all the various animations that the player has
	int Action;//tracks which action is being performed by the main character
	double MouseAngleRadians;//angle of mouse in radians. Used to track which direction the player faces (check flags)

	String *string = new String();

public:
	Player();
	void Init(double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY, ALLEGRO_BITMAP *PlayerImage);
	void Update();
	void Render(double cameraXPos, double cameraYPos);

	//==============================================
	//MOVEMENT
	//==============================================
	void PlayerKeyboard(bool UP, bool DOWN, bool LEFT, bool RIGHT, bool SHIFT);
	void AnimationHandler();//stores what row of animations corresponds to what animation. Can also be expanded to modify specific player characteristics (size, position, velocity, etc).

	//==============================================
	//MOUSEANGLE
	//==============================================
	double GetMouseAngleRadians() { return MouseAngleRadians; }
	void SetMouseAngleRadians(double MouseAngleRadians) { Player::MouseAngleRadians = MouseAngleRadians; }
};