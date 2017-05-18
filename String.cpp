#include "String.h"
#include "StringJoint.h"

String::String() {}

void String::Init(double x, double y, int StringJointNum, int StringJointSpacing, int StringJointW, int StringJointH)
{
	//String::StringJointNum = StringJointNum;
	//String::StringJointSpacing = StringJointSpacing;
	//String::StringJointW = StringJointW;
	//String::StringJointH = StringJointH;

	for (int a = 2; a <= StringJointNum; a++) {
		StringJoint *joint = new StringJoint();
		joint->Init(a, x, y, (a), StringJointSpacing, StringJointNum, StringJointW, StringJointH);//velocity is exponential, dependent on joint number
		JointList.push_back(joint);
	}
}

void String::Update(double x, double y, double dirX, double dirY, double cameraXPos, double cameraYPos)
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
		(*jiter)->Update(x, y, dirX, dirY, SwayChange, SpeedChange, cameraXPos, cameraYPos);
	}
	//cout << x << ", " << y << " : " << dirX << ", " << dirY << endl;
}

double String::GetLowestPoint() {
	int LowestPoint = 0;
	for (jiter = JointList.begin(); jiter != JointList.end(); ++jiter)
	{
		if ((*jiter)->GetJointYPos() > LowestPoint)
			LowestPoint = (*jiter)->GetJointYPos();
	}
	return LowestPoint;
}