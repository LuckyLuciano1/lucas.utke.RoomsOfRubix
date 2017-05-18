#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include "String.h"
#include <vector>
using namespace std;

class StringJoint : public Object
{
private:
	double JointXDir;
	double JointYDir;

	double JointXPos;
	double JointYPos;

	double Vel;//speed at which String "rubber bands"

	int JointID;//tracks what number the joint is on the String

	int StringJointSpacing;
	int StringJointNum;
	int StringJointW;
	int StringJointH;

	double WindCounter;//number used in sin() equation
	double WindSway;//degree to which String sways
	double WindSpeed;//speed at which String sways

public:
	StringJoint();
	void Init(int JointID, double JointXPos, double JointYPos, double Vel, int StringJointSpacing, int StringJointNum, int StringJointW, int StringJointH);
	void Update(double x, double y, double dirX, double dirY, double SwayChange, double SpeedChange, double cameraXPos, double cameraYPos);

	double GetJointXPos() { return JointXPos; }
	double GetJointYPos() { return JointYPos; }
};