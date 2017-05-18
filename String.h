#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include "StringJoint.h"
#include <vector>
using namespace std;

class String : public Object
{
private:
	//int StringJointNum;
	//int StringJointSpacing;
	//int StringJointW;
	//int StringJointH;

	vector<StringJoint *> JointList;//holds joints
	vector<StringJoint *>::iterator jiter;

public:
	String();
	void Init(double x, double y, int StringJointNum, int StringJointSpacing, int StringJointW, int StringJointH);
	void Update(double x, double y, double dirX, double dirY, double cameraXPos, double cameraYPos);
	double GetLowestPoint();
};