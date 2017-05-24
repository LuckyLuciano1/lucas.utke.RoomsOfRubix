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

	WindCounter = 0;//makes line
					//WindCounter = JointID;//makes spiral cone

	WindSpeed = .03;
	WindSway = .22;
}

void PlayerCloakJoint::Update(double x, double y, double dirX, double dirY, double cameraXPos, double cameraYPos)
{
	//if (dirX == 0 && dirY == 0) {//setting up 'resting position' of String when player/object is in idle state
	//	dirX = 0;
	//	dirY = -1;
	//}

	//JointXDir = ((((JointXPos - x)/*current position*/ + (JointID*PlayerCloakJointSpacing)*dirX)/*displacement*/ / Vel));// +WindSway*sin(WindCounter += WindSpeed) + WindSway / 2);//Vel of String is dependent on distance from object
	//JointYDir = ((((JointYPos - y)/*currentposition*/ + (JointID*PlayerCloakJointSpacing)*-dirY)/*displacement*/ / Vel));

	//JointXDir = (((JointXPos - x) + ((JointID*PlayerCloakJointSpacing)*dirX) / 6) / Vel);// +WindSway*sin(WindCounter += WindSpeed) + WindSway / 2;
	//JointYDir = (((JointYPos - y) - (JointID*PlayerCloakJointSpacing)));

	//JointXDir = (cameraXPos)+(x + dirX) / Vel;//velocity of camera is dependent on distance from object
	//JointYDir = (cameraYPos)+(y + dirY) / Vel;

	curXPos = JointXPos;//recording previous position as current position for dir calculation
	curYPos = JointYPos;

	JointXPos = x + (WindSway*sin(WindCounter += WindSpeed) + WindSway / 2)*Vel;//creates swaying in wind
	JointYPos = y + (JointID*PlayerCloakJointSpacing);//displaces points downward

	//JointXDir = (Vel/(curXPos-JointXPos)/*velocity proportional to distance from resting position*/);
	//JointYDir = (Vel/(curYPos-JointYPos)/*velocity proportional to distance from resting position*/);
	//cout << JointXDir << ", " << JointYDir << endl;
	//JointXPos -= JointXDir;
	//JointYPos -= JointYDir;

	al_draw_filled_rectangle((JointXPos -= JointXDir) + cameraXPos, (JointYPos -= JointYDir) + cameraYPos, ((JointXPos -= JointXDir)+cameraXPos) + PlayerCloakJointW, ((JointYPos -= JointYDir) + cameraYPos) + PlayerCloakJointH, al_map_rgb((81 + JointID), 75, 69));//brown cloak
	
	//al_draw_filled_rectangle((JointXPos+cameraXPos), (JointYPos+cameraYPos), (JointXPos + cameraXPos)+5, (JointYPos + cameraYPos)+5, al_map_rgb(255, 255, 255));

	//double a = ((x + cameraXPos) + ((JointID*PlayerCloakJointSpacing)*-dirX) / 6);
	//double b = ((y + cameraYPos) + (JointID*PlayerCloakJointSpacing));
	//al_draw_filled_rectangle(a, b, a + PlayerCloakJointW, b + PlayerCloakJointH, al_map_rgb((81 + JointID), 75, 69));
	//al_draw_filled_rectangle(JointXPos + cameraXPos, JointYPos + cameraYPos, (JointXPos + cameraXPos) + PlayerCloakJointW, (JointYPos + cameraYPos) + PlayerCloakJointH, al_map_rgb((81 + JointID), 75, 69));//path of cloak



	//al_draw_filled_rectangle(JointXPos + JointXDir + cameraXPos, JointYPos + JointYDir + cameraYPos, (JointXPos + JointXDir + cameraXPos) + PlayerCloakJointW, (JointYPos + JointYDir + cameraYPos) + PlayerCloakJointH, al_map_rgb((170 + JointID), 100, 30));//orange hair
	//al_draw_filled_rectangle(JointXPos - JointXDir + cameraXPos, JointYPos - JointYDir + cameraYPos, (JointXPos - JointXDir + cameraXPos) + PlayerCloakJointW, (JointYPos - JointYDir + cameraYPos) + PlayerCloakJointH, al_map_rgb((81 - JointID), 75, 69));//crimson scarf
}