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
	WindSway = .2;
}

void PlayerCloakJoint::Update(double x, double y, double dirX, double dirY, double cameraXPos, double cameraYPos)
{
	if (dirX == 0 && dirY == 0) {//setting up 'resting position' of String when player/object is in idle state
		dirX = 0;
		dirY = 1;
	}
	JointXDir = ((((JointXPos - x)/*current position*/ + (JointID*PlayerCloakJointSpacing)*dirX)/*displacement*/ / Vel));// +WindSway*sin(WindCounter += WindSpeed) + WindSway / 2);//Vel of String is dependent on distance from object
	JointYDir = ((((JointYPos - y)/*currentposition*/+(JointID*PlayerCloakJointSpacing)*-dirY)/*displacement*/ / Vel));

	JointXPos -= JointXDir;
	JointYPos -= JointYDir;

	//al_draw_filled_rectangle(JointXPos - JointXDir + cameraXPos, JointYPos - JointYDir + cameraYPos, (JointXPos - JointXDir + cameraXPos) + PlayerCloakJointW, (JointYPos - JointYDir + cameraYPos) + PlayerCloakJointH, al_map_rgb((81 - JointID), 75, 69));//crimson scarf
	al_draw_filled_rectangle(JointXPos + cameraXPos, JointYPos + cameraYPos, (JointXPos + cameraXPos) + PlayerCloakJointW, (JointYPos + cameraYPos) + PlayerCloakJointH, al_map_rgb((81 + JointID), 75, 69));//brown cloak
	//al_draw_filled_rectangle(JointXPos + JointXDir + cameraXPos, JointYPos + JointYDir + cameraYPos, (JointXPos + JointXDir + cameraXPos) + PlayerCloakJointW, (JointYPos + JointYDir + cameraYPos) + PlayerCloakJointH, al_map_rgb((170 + JointID), 100, 30));//orange hair
	/*dirX = 1;
	dirY = 1;
	*/
	if (dirX == 1 && dirY == 0) { dirX /= -1 / 2, dirY /= -sqrt(3) / 2; }
	else if (dirX == 0 && dirY == 0) { dirX /= 0, dirY /= -1; }
	else if (dirX == 1 && dirY == 1) { dirX /= sqrt(2) / 2, dirY/=sqrt(2) / 2; }
	else if (dirX == 0 && dirY == 1) { dirX/=0, dirY/=-1; }

	else if (dirX == -1 && dirY == 0) { dirX/=1 / 2, dirY/=-sqrt(3) / 2; }
	else if (dirX == -1 && dirY == -1) { dirX/=-sqrt(2) / 2, dirY/=-sqrt(2) / 2; }
	else if (dirX == 0 && dirY == -1) { dirX/=0, dirY/=-1; }
	else
		cout << "wha?" << endl;

	//dirX *= (sqrt(2.0) / 2.0);
	//dirY *= (sqrt(2.0) / 2.0);

	double a = (x + cameraXPos + ((JointID*PlayerCloakJointSpacing)*dirX));
	double b = (y + cameraYPos + ((JointID*PlayerCloakJointSpacing)*dirY));
	al_draw_filled_rectangle(a, b, a + 3, b + 3, al_map_rgb(255, 255, 255));
}