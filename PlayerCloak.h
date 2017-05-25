#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include "PlayerCloakJoint.h"
#include <vector>
using namespace std;

class PlayerCloak : public Object
{
private:

	vector<PlayerCloakJoint *> JointList;//holds joints
	vector<PlayerCloakJoint *>::iterator jiter;

public:
	PlayerCloak();
	void Init(double x, double y, int PlayerCloakJointNum, int PlayerCloakJointSpacing, int PlayerCloakJointW, int PlayerCloakJointH, int ColorR, int ColorG, int ColorB);
	void Update(double z, double dirX, double dirY,double velX, double velY, double cameraXPos, double cameraYPos);
};