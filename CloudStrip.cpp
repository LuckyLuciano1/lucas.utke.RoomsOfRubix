#include "CloudStrip.h"
#include "DecorCircle.h"
#include "DecorBox.h"

CloudStrip::CloudStrip() {}//CloudStrip is an object with no collision that renders a simple box

void CloudStrip::Init(double x, double y, double z, double boundX, int RadiusRange, int RadiusMin, double velX, int R, int G, int B)
{
	Object::Init(x, y, z);
	Object::SetBoundX(boundX);
	CloudStrip::R = R;//color of box
	CloudStrip::G = G;
	CloudStrip::B = B;

	for (int a = x; a < boundX;) {
		int Radius = rand() % RadiusRange + RadiusMin;
		a += Radius;
		DecorCircle *CloudPiece = new DecorCircle();	
		CloudPiece->Init(a, y, z, Radius, R, G, B, false);
		AllObjectsList.push_back(CloudPiece);
	}



	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)//making clouds move
	{
		(*iter)->SetVelX(velX);
		(*iter)->SetDirX(-1);
	}

	//CloudBottom = new DecorBox();//should not move
	CloudBottom->Init(x, y, z, boundX, RadiusMin + RadiusRange, R, G, B);
}

void CloudStrip::Update()
{
	Object::Update();//updating cloudstrip itself
	CloudBottom->Update();
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
		(*iter)->Update();
		if ((*iter)->GetDirX() < 0 && (*iter)->GetX() + (*iter)->GetRadius() < x)//if moving left and has exceeded bounds of cloud strip, reset to beginning of strip
			(*iter)->SetX(x + boundX+(*iter)->GetRadius());
		else if ((*iter)->GetDirX() > 0 && (*iter)->GetX() - (*iter)->GetRadius() > x + boundX)//same except right
			(*iter)->SetX(x - (*iter)->GetRadius());
	}
}

void CloudStrip::Render(double cameraXPos, double cameraYPos)
{
	CloudBottom->Render(cameraXPos, cameraYPos);
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
			(*iter)->Render(cameraXPos, cameraYPos);
	}
}