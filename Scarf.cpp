#include "Scarf.h"
#include "ScarfJoint.h"

Scarf::Scarf() {}

void Scarf::Init(double x, double y, int ScarfJointNum, int ScarfJointSpacing)
{
	Scarf::ScarfJointNum = ScarfJointNum;
	Scarf::ScarfJointSpacing = ScarfJointSpacing;

	Wind = 0;
	WindDirection = false;

	for (int a = 2; a <= ScarfJointNum; a++) {
		ScarfJoint *joint = new ScarfJoint();
		joint->Init(a, x, y, (a), ScarfJointSpacing);//velocity is exponential, dependent on joint number
		JointList.push_back(joint);
	}

}

void Scarf::Update(double x, double y)
{
	if (Wind > 10)
		WindDirection = false;

	if (Wind < -10)
		WindDirection = true;

	if (WindDirection)
		Wind+=2;
	else
		Wind-=2;

	for (jiter = JointList.begin(); jiter != JointList.end(); ++jiter)
	{
		(*jiter)->MoveTo(x + Wind, y);
	}
	//cout << x << ", " << y << " : " << dirX << ", " << dirY << endl;
}