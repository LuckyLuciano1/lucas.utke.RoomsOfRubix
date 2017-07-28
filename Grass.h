#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include "GrassJoint.h"
#include <vector>
using namespace std;

class Grass : public Object
{
private:
	//int GrassJointNum;
	//int GrassJointSpacing;
	//int GrassJointW;
	//int GrassJointH;

	vector<GrassJoint *> JointList;//holds joints
	vector<GrassJoint *>::iterator jiter;

public:
	Grass();
	void Init(double x, double y, double z, int GrassJointNum, int GrassJointSpacing, int GrassJointW, int GrassJointH);
	void Render(double cameraXPos, double cameraYPos);
	void Update();
	double GetLowestPoint();
};