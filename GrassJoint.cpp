#include "Grass.h"
#include "GrassJoint.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

GrassJoint::GrassJoint() {}

void GrassJoint::Init(int JointID, double JointXPos, double JointYPos, double Vel, int GrassJointSpacing, int GrassJointNum, int GrassJointW, int GrassJointH)
{
	GrassJoint::JointXPos = JointXPos;
	GrassJoint::JointYPos = JointYPos;
	JointXDir = 0;
	JointYDir = 0;
	GrassJoint::Vel = Vel;
	GrassJoint::JointID = JointID;

	GrassJoint::GrassJointSpacing = GrassJointSpacing;
	GrassJoint::GrassJointNum = GrassJointNum;
	GrassJoint::GrassJointW = GrassJointW;
	GrassJoint::GrassJointH = GrassJointH;

	WindCounter = 0;//makes line
					//WindCounter = JointID;//makes spiral cone

	WindSpeed = .03;
	WindSway = 1;
}

void GrassJoint::Update(double x, double y, double z, double dirX, double dirY, double SwayChange, double SpeedChange, double cameraXPos, double cameraYPos)
{

	if (dirX == 0 && dirY == 0) {//setting up 'resting position' of Grass when player/object is in idle state
		dirX = 0;
		dirY = 1;
	}
	if(WindSway + SwayChange/100 < 1.5 && WindSway + SwayChange / 100 > .5)
		WindSway += SwayChange / 100;
	if(WindSpeed + SpeedChange/100 < .08 && WindSpeed + SwayChange / 100 > .01)
	WindSpeed += SpeedChange / 100;

	//WindSway = sin(WindCounter + WindSpeed);//makes spirals

	JointXDir = (((JointXPos + JointXDir) - (x)+(JointID*GrassJointSpacing)*dirX) / Vel) + WindSway*sin(WindCounter += WindSpeed) + WindSway/1.5;//Vel of Grass is dependent on distance from object
	JointYDir = ((JointYPos + JointYDir) - ((y)+(JointID*GrassJointSpacing)*-dirY)) / Vel;

	JointXPos -= JointXDir;
	JointYPos -= JointYDir;

	
	al_draw_filled_rectangle(JointXPos + cameraXPos, JointYPos + cameraYPos + z, (JointXPos + cameraXPos) + GrassJointW, (JointYPos + cameraYPos) + GrassJointH + z, al_map_rgb(120 + JointID*2, 150, 80));
	//al_draw_filled_rectangle(JointXPos + cameraXPos, JointYPos + cameraYPos, (JointXPos + cameraXPos) + GrassJointW*WindSway*sin(WindCounter + WindSpeed), (JointYPos + cameraYPos) + GrassJointH*WindSway*sin(WindCounter + WindSpeed), al_map_rgb((JointID * 3 - 175), 23, 23));//varies color+size

}