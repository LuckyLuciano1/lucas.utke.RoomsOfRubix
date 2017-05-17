#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include "Scarf.h"
#include <vector>
using namespace std;

class ScarfJoint : public Object
{
private:
	double JointXDir;
	double JointYDir;

	double JointXPos;
	double JointYPos;

	double Vel;//speed at which scarf "rubber bands"

	int JointID;//tracks what number the joint is on the scarf

	int ScarfJointSpacing;
public:
	ScarfJoint();
	void Init(int JointID, double JointXPos, double JointYPos, double Vel, int ScarfJointSpacing);
	void MoveTo(double x, double y);
};