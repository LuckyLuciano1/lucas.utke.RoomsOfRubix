#include "PlayerCloak.h"
#include "PlayerCloakJoint.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

PlayerCloakJoint::PlayerCloakJoint() {}

void PlayerCloakJoint::Init(int JointID, double JointXPos, double JointYPos, double Vel, int PlayerCloakJointSpacing, int PlayerCloakJointNum, int PlayerCloakJointW, int PlayerCloakJointH)
{
	PlayerCloakJoint::JointXPos = JointXPos;
	PlayerCloakJoint::JointYPos = JointYPos;
	JointXDir = 0;
	JointYDir = 0;
	PlayerCloakJoint::Vel = Vel;
	PlayerCloakJoint::JointID = JointID;

	PlayerCloakJoint::PlayerCloakJointSpacing = PlayerCloakJointSpacing;
	PlayerCloakJoint::PlayerCloakJointNum = PlayerCloakJointNum;
	PlayerCloakJoint::PlayerCloakJointW = PlayerCloakJointW;
	PlayerCloakJoint::PlayerCloakJointH = PlayerCloakJointH;


	PlayerCloakJoint::SetPointX = JointXPos;
	PlayerCloakJoint::SetPointY = JointYPos;


	WindCounter = 0;//makes line
					//WindCounter = JointID;//makes spiral cone

	WindSpeed = .03;
	WindSway = 1;
}

void PlayerCloakJoint::Update(double x, double y, double dirX, double dirY, double cameraXPos, double cameraYPos)
{

	if (dirX == 0 && dirY == 0) {//setting up 'resting position' of String when player/object is in idle state
		dirX = 0;
		dirY = -1;
	}

	JointXDir = (((JointXPos + JointXDir) - (SetPointX - x)+(JointID*PlayerCloakJointSpacing)*(dirX))/Vel);// +WindSway*sin(WindCounter += WindSpeed) + WindSway / 2;//Vel of String is dependent on distance from object
	JointYDir = (((JointYPos + JointYDir) - (SetPointY - x) + (JointID*PlayerCloakJointSpacing)*(-dirY))/Vel);

	JointXPos -= JointXDir;
	JointYPos -= JointYDir;

	//JointXDir = (((JointXPos + JointXDir) - (SetPointX)+(JointID*PlayerCloakJointSpacing))/Vel);

	//al_draw_filled_rectangle(JointXPos - JointXDir + cameraXPos, JointYPos - JointYDir + cameraYPos, (JointXPos - JointXDir + cameraXPos) + PlayerCloakJointW, (JointYPos - JointYDir + cameraYPos) + PlayerCloakJointH, al_map_rgb((81 - JointID), 75, 69));

	//al_draw_filled_rectangle(JointXPos + cameraXPos, JointYPos + cameraYPos, (JointXPos + cameraXPos) + PlayerCloakJointW, (JointYPos + cameraYPos) + PlayerCloakJointH, al_map_rgb((81 + JointID), 75, 69));//cloak brown
	al_draw_filled_rectangle(JointXPos + cameraXPos, JointYPos + cameraYPos, (JointXPos + cameraXPos) + PlayerCloakJointW, (JointYPos + cameraYPos) + PlayerCloakJointH, al_map_rgb((170 + JointID), 100, 30));//orange hair
}