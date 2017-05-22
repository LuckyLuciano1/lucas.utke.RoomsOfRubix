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

	double JointXPos;
	double JointYPos;

	double Vel;//speed at which String "rubber bands"

	int JointID;//tracks what number the joint is on the String

	int PlayerCloakJointSpacing;
	int PlayerCloakJointNum;
	int PlayerCloakJointW;
	int PlayerCloakJointH;

	double WindCounter;//number used in sin() equation
	double WindSway;//degree to which String sways
	double WindSpeed;//speed at which String sways

	double SetPointX;//point that joint is rubber banding from
	double SetPointY;


public:
	PlayerCloakJoint();
	void Init(int JointID, double JointXPos, double JointYPos, double Vel, int PlayerCloakJointSpacing, int PlayerCloakJointNum, int PlayerCloakJointW, int PlayerCloakJointH);
	void Update(double x, double y, double dirX, double dirY, double cameraXPos, double cameraYPos);

	double GetJointXPos() { return JointXPos; }
	double GetJointYPos() { return JointYPos; }
};