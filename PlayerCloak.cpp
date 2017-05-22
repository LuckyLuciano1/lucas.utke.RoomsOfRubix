#include "PlayerCloak.h"
#include "PlayerCloakJoint.h"

PlayerCloak::PlayerCloak() {}

void PlayerCloak::Init(double x, double y, int PlayerCloakJointNum, int PlayerCloakJointSpacing, int PlayerCloakJointW, int PlayerCloakJointH)
{

	for (int a = 2; a <= PlayerCloakJointNum; a++) {
		PlayerCloakJoint *joint = new PlayerCloakJoint();
		joint->Init(a, x, y, (a), PlayerCloakJointSpacing, PlayerCloakJointNum, PlayerCloakJointW, PlayerCloakJointH);//velocity is exponential, dependent on joint number
		JointList.push_back(joint);
	}
}

void PlayerCloak::Update(double x, double y, double dirX, double dirY, double cameraXPos, double cameraYPos)
{
	double SpeedChange = 0;
	double SwayChange = 0;

	/*if (rand() % 60 == 1) {
	SpeedChange = rand() % 2 + 1;
	if (rand() % 2 == 1)
	SpeedChange *= -1;
	SwayChange = (rand() % 5 + 1) / 1;
	if (rand() % 2 == 1)
	SwayChange *= -1;
	}*/
	for (jiter = JointList.begin(); jiter != JointList.end(); ++jiter)
	{
		(*jiter)->Update(x, y, dirX, dirY, cameraXPos, cameraYPos);
	}
	//cout << x << ", " << y << " : " << dirX << ", " << dirY << endl;
}

double PlayerCloak::GetLowestPoint() {
	int LowestPoint = 0;
	for (jiter = JointList.begin(); jiter != JointList.end(); ++jiter)
	{
		if ((*jiter)->GetJointYPos() > LowestPoint)
			LowestPoint = (*jiter)->GetJointYPos();
	}
	return LowestPoint;
}