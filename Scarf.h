#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include "ScarfJoint.h"
#include <vector>
using namespace std;

class Scarf : public Object
{
private:
	int ScarfJointNum;
	int ScarfJointSpacing;

	int Wind;//shifts x variable back and forth
	bool WindDirection;

	vector<ScarfJoint *> JointList;//holds joints
	vector<ScarfJoint *>::iterator jiter;

public:
	Scarf();
	void Init(double x, double y, int ScarfJointNum, int ScarfJointSpacing);
	void Update(double x, double y);
};