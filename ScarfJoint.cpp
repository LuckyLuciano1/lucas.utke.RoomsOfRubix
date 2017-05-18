#include "Scarf.h"
#include "ScarfJoint.h"

ScarfJoint::ScarfJoint() {}

void ScarfJoint::Init(int JointID, double JointXPos, double JointYPos, double Vel, int ScarfJointSpacing, int ScarfJointNum)
{
	ScarfJoint::JointXPos = JointXPos;
	ScarfJoint::JointYPos = JointYPos;
	JointXDir = 0;
	JointYDir = 0;
	ScarfJoint::Vel = Vel;
	ScarfJoint::JointID = JointID;
	ScarfJoint::ScarfJointSpacing = ScarfJointSpacing;
	ScarfJoint::ScarfJointNum = ScarfJointNum;

	//WindCounter = 0;//makes line
	WindCounter = JointID;//makes cone
	
	WindSpeed = .03;
	WindSway = 1;
}

void ScarfJoint::MoveTo(double x, double y, double dirX, double dirY)
{

	if (dirX == 0 && dirY == 0){//setting up 'resting position' of scarf when player is in idle state
	dirX = 0;
	dirY = -1;
	}

	//WindSway = sin(WindCounter + WindSpeed);//makes spirals

	JointXDir = (((JointXPos + JointXDir) - (x)+(JointID*ScarfJointSpacing)*dirX) / Vel) + WindSway*sin(WindCounter += WindSpeed);//Vel of Scarf is dependent on distance from object
	JointYDir = ((JointYPos + JointYDir) - ((y) + (JointID*ScarfJointSpacing)*-dirY)) / Vel;

	JointXPos -= JointXDir;
	JointYPos -= JointYDir;

	//al_draw_filled_rectangle(JointXPos, JointYPos, JointXPos+10, JointYPos+10, al_map_rgb(175, 23, 23));
	al_draw_filled_rectangle(JointXPos, JointYPos, JointXPos+ WindSway*10*sin(WindCounter + WindSpeed), JointYPos+ WindSway*10*sin(WindCounter + WindSpeed), al_map_rgb((JointID - 175), 23, 23));//varies size sinusoidally
}