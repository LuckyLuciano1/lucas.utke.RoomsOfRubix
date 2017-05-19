#include "Grass.h"
#include "GrassJoint.h"

Grass::Grass() {}

void Grass::Init(double x, double y, int GrassJointNum, int GrassJointSpacing, int GrassJointW, int GrassJointH)
{
	//Grass::GrassJointNum = GrassJointNum;
	//Grass::GrassJointSpacing = GrassJointSpacing;
	//Grass::GrassJointW = GrassJointW;
	//Grass::GrassJointH = GrassJointH;
	Grass::ObjX = x;
	Grass::ObjY = y;

	for (int a = 2; a <= GrassJointNum; a++) {
		GrassJoint *joint = new GrassJoint();
		joint->Init(a, x, y, (a), GrassJointSpacing, GrassJointNum, GrassJointW, GrassJointH);//velocity is exponential, dependent on joint number
		JointList.push_back(joint);
	}
}

void Grass::Update(double cameraXPos, double cameraYPos)
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
		(*jiter)->Update(ObjX, ObjY, 0, 1, SwayChange, SpeedChange, cameraXPos, cameraYPos);
	}
	//cout << x << ", " << y << " : " << dirX << ", " << dirY << endl;
}

double Grass::GetLowestPoint() {
	int LowestPoint = 0;
	for (jiter = JointList.begin(); jiter != JointList.end(); ++jiter)
	{
		if ((*jiter)->GetJointYPos() > LowestPoint)
			LowestPoint = (*jiter)->GetJointYPos();
	}
	return LowestPoint;
}