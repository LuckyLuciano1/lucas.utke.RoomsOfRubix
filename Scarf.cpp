#include "Scarf.h"
#include "ScarfJoint.h"

Scarf::Scarf() {}

void Scarf::Init(double x, double y, int ScarfJointNum, int ScarfJointSpacing)
{
	Scarf::ScarfJointNum = ScarfJointNum;
	Scarf::ScarfJointSpacing = ScarfJointSpacing;

	for (int a = 2; a <= ScarfJointNum; a++) {
		ScarfJoint *joint = new ScarfJoint();
		joint->Init(a, x, y, (a), ScarfJointSpacing, ScarfJointNum);//velocity is exponential, dependent on joint number
		JointList.push_back(joint);
	}

}

void Scarf::Update(double x, double y, double dirX, double dirY)
{
	for (jiter = JointList.begin(); jiter != JointList.end(); ++jiter)
	{
		(*jiter)->MoveTo(x, y, dirX, dirY);
	}
	//cout << x << ", " << y << " : " << dirX << ", " << dirY << endl;
}