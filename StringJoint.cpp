#include "String.h"
#include "StringJoint.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

StringJoint::StringJoint() {}

void StringJoint::Init(int JointID, double JointXPos, double JointYPos, double Vel, int StringJointSpacing, int StringJointNum, int StringJointW, int StringJointH)
{
	StringJoint::JointXPos = JointXPos;
	StringJoint::JointYPos = JointYPos;
	JointXDir = 0;
	JointYDir = 0;
	StringJoint::Vel = Vel;
	StringJoint::JointID = JointID;

	StringJoint::StringJointSpacing = StringJointSpacing;
	StringJoint::StringJointNum = StringJointNum;
	StringJoint::StringJointW = StringJointW;
	StringJoint::StringJointH = StringJointH;

	WindCounter = 0;//makes line
	//WindCounter = JointID;//makes spiral cone

	WindSpeed = .03;
	WindSway = 1;
}

void StringJoint::Update(double x, double y, double dirX, double dirY, double SwayChange, double SpeedChange, double cameraXPos, double cameraYPos)
{

	if (dirX == 0 && dirY == 0) {//setting up 'resting position' of String when player/object is in idle state
		dirX = 0;
		dirY = -1;
	}
	WindSway += SwayChange / 100;
	WindSpeed += SpeedChange / 100;

	//WindSway = sin(WindCounter + WindSpeed);//makes spirals

	JointXDir = (((JointXPos + JointXDir) - (x)+(JointID*StringJointSpacing)*dirX) / Vel) + WindSway*sin(WindCounter += WindSpeed) + WindSway / 2;//Vel of String is dependent on distance from object
	JointYDir = ((JointYPos + JointYDir) - ((y)+(JointID*StringJointSpacing)*-dirY)) / Vel;

	JointXPos -= JointXDir;
	JointYPos -= JointYDir;


	al_draw_filled_rectangle(JointXPos + cameraXPos, JointYPos + cameraYPos, (JointXPos + cameraXPos) + StringJointW, (JointYPos + cameraYPos) + StringJointH, al_map_rgb((175 - JointID), 23, 23));
	//al_draw_filled_rectangle(JointXPos + cameraXPos, JointYPos + cameraYPos, (JointXPos + cameraXPos) + StringJointW*WindSway*sin(WindCounter + WindSpeed), (JointYPos + cameraYPos) + StringJointH*WindSway*sin(WindCounter + WindSpeed), al_map_rgb((JointID*WindSway*sin(WindCounter + WindSpeed) - 175), 23, 23));//varies color+size

}