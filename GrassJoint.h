#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include "Grass.h"
#include <vector>
using namespace std;

class GrassJoint : public Object
{
private:
	double JointXDir;
	double JointYDir;

	double JointXPos;
	double JointYPos;

	double Vel;//speed at which Grass "rubber bands"

	int JointID;//tracks what number the joint is on the Grass

	int GrassJointSpacing;
	int GrassJointNum;
	int GrassJointW;
	int GrassJointH;

	double WindCounter;//number used in sin() equation
	double WindSway;//degree to which Grass sways
	double WindSpeed;//speed at which Grass sways

public:
	GrassJoint();
	void Init(int JointID, double JointXPos, double JointYPos, double Vel, int GrassJointSpacing, int GrassJointNum, int GrassJointW, int GrassJointH);
	void Update(double x, double y, double dirX, double dirY, double SwayChange, double SpeedChange, double cameraXPos, double cameraYPos);

	double GetJointXPos() { return JointXPos; }
	double GetJointYPos() { return JointYPos; }
};