#include "PlayerCloak.h"
#include "PlayerCloakJoint.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

PlayerCloakJoint::PlayerCloakJoint() {}

void PlayerCloakJoint::Init(int JointID, double JointXPos, double JointYPos, double Vel, int PlayerCloakJointSpacing, int PlayerCloakJointNum, int PlayerCloakJointW, int PlayerCloakJointH, int ColorR, int ColorG, int ColorB)
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

	PlayerCloakJoint::ColorR = ColorR;
	PlayerCloakJoint::ColorG = ColorG;
	PlayerCloakJoint::ColorB = ColorB;


	WindCounter = 0;
	WindSpeed = .03;
	WindSway = 1;
}

void PlayerCloakJoint::Update(double z, double dirX, double dirY, double velX, double velY, double cameraXPos, double cameraYPos)
{
	JointXPos += dirX*velX;//updating position of object and correspondent resting point
	JointYPos += dirY*velY;

	JointXDir = ((CurXPos)-(JointXPos)) / (Vel) + WindSway*sin(WindCounter += WindSpeed) + WindSway / 2;//determining direction based on current point compared to resting point
	JointYDir = ((CurYPos)-(JointYPos)) / (Vel);// (Vel / 10.0);

	CurXPos -= JointXDir;//updating current position according to direction
	CurYPos -= JointYDir;

	al_draw_filled_rectangle((CurXPos + cameraXPos), (CurYPos + cameraYPos) + z, (CurXPos + cameraXPos) + PlayerCloakJointW, (CurYPos + cameraYPos) + PlayerCloakJointH + z, al_map_rgb((ColorR + JointID), ColorG, ColorB));

	//al_draw_filled_rectangle(JointXPos + JointXDir + cameraXPos, JointYPos + JointYDir + cameraYPos, (JointXPos + JointXDir + cameraXPos) + PlayerCloakJointW, (JointYPos + JointYDir + cameraYPos) + PlayerCloakJointH, al_map_rgb((170 + JointID), 100, 30));//orange hair
	//al_draw_filled_rectangle(JointXPos - JointXDir + cameraXPos, JointYPos - JointYDir + cameraYPos, (JointXPos - JointXDir + cameraXPos) + PlayerCloakJointW, (JointYPos - JointYDir + cameraYPos) + PlayerCloakJointH, al_map_rgb((81 - JointID), 75, 69));//crimson scarf
}