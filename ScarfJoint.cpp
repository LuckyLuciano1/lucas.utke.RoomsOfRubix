#include "Scarf.h"
#include "ScarfJoint.h"

ScarfJoint::ScarfJoint() {}

void ScarfJoint::Init(int JointID, double JointXPos, double JointYPos, double Vel, int ScarfJointSpacing)
{
	ScarfJoint::JointXPos = JointXPos;
	ScarfJoint::JointYPos = JointYPos;
	JointXDir = 0;
	JointYDir = 0;
	ScarfJoint::Vel = Vel;
	ScarfJoint::JointID = JointID;
	ScarfJoint::ScarfJointSpacing = ScarfJointSpacing;
}

void ScarfJoint::MoveTo(double x, double y)
{
	//Object::Update();
	JointXDir = ((JointXPos + JointXDir) - x) / Vel;//Vel of Scarf is dependent on distance from object
	JointYDir = ((JointYPos + JointYDir) - (y + (JointID*ScarfJointSpacing))) / Vel;


	JointXPos -= JointXDir;
	JointYPos -= JointYDir;

	al_draw_filled_rectangle(JointXPos, JointYPos, JointXPos+10, JointYPos+10, al_map_rgb(255, 0, 0));
	//cout << "player: " << x << ", " << y + (JointID*ScarfJointSpacing)<< endl;
	cout <<JointID<<": "<< x<<", "<<y<<"->"<<JointXPos << ", " << JointYPos << endl;
}