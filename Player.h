#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
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
	int Animation;//tracks which animation is being performed by the main character
	double MouseAngleRadians;//angle of mouse in radians. Used to track which direction the player faces (check flags)
public:
	Player();
	void Init(double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY, ALLEGRO_BITMAP *PlayerImage);
	void Update(double cameraXDir, double cameraYDir);

	//==============================================
	//MOVEMENT
	//==============================================
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void ResetAnimation(int position);

	void AnimationHandler();
};