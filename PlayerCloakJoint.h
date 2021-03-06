#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include "PlayerCloak.h"
#include <vector>
using namespace std;

class PlayerCloakJoint : public Object
{
private:
	double JointXDir;
	double JointYDir;

	double JointXPos;//resting position of object
	double JointYPos;

	double CurXPos;//current position of object
	double CurYPos;

	double Vel;//speed at which String "rubber bands"

	int JointID;//tracks what number the joint is on the String

	int PlayerCloakJointSpacing;
	int PlayerCloakJointNum;

	int PlayerCloakJointW;
	int PlayerCloakJointH;

	double WindCounter;//number used in sin() equation
	double WindSway;//degree to which String sways
	double WindSpeed;//speed at which String sways

	int ColorR;//colors of Cloak. only accurately describes top of cloak.
	int ColorG;
	int ColorB;

public:
	PlayerCloakJoint();
	void Init(int JointID, double JointXPos, double JointYPos, double Vel, int PlayerCloakJointSpacing, int PlayerCloakJointNum, int PlayerCloakJointW, int PlayerCloakJointH, int ColorR, int ColorG, int COlorB);
	void Update(double z, double dirX, double dirY, double velX, double velY, double cameraXPos, double cameraYPos);
};