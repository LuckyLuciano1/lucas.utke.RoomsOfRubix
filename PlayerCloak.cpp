#include "PlayerCloak.h"
#include "PlayerCloakJoint.h"

PlayerCloak::PlayerCloak() {}

void PlayerCloak::Init(double x, double y, int PlayerCloakJointNum, int PlayerCloakJointSpacing, int PlayerCloakJointW, int PlayerCloakJointH, int ColorR, int ColorG, int ColorB)
{

	for (int a = 10; a <= PlayerCloakJointNum; a++) {
		if (a > PlayerCloakJointW/2) {//second half
			PlayerCloakJoint *joint = new PlayerCloakJoint();
			joint->Init(a, x + (a)/2, y+a, (a*a)/(10.00*(a/2)), PlayerCloakJointSpacing, PlayerCloakJointNum, (PlayerCloakJointNum - a), PlayerCloakJointH, ColorR, ColorG, ColorB);//velocity is exponential, dependent on joint number
			JointList.push_back(joint);
		}
		else{//first half
			PlayerCloakJoint *joint = new PlayerCloakJoint();
			joint->Init(a, x + (PlayerCloakJointW - a)/2, y+a, (a*a)/(10.00*(a/2)), PlayerCloakJointSpacing, PlayerCloakJointNum, a, PlayerCloakJointH, ColorR, ColorG, ColorB);//velocity is exponential, dependent on joint number
			JointList.push_back(joint);
		}

	}
}

void PlayerCloak::Update(double z, double dirX, double dirY, double velX, double velY, double cameraXPos, double cameraYPos)
{
	for (jiter = JointList.begin(); jiter != JointList.end(); ++jiter)
	{
		(*jiter)->Update(z, dirX, dirY, velX, velY, cameraXPos, cameraYPos);
	}
}