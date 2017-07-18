#include "CloudStrip.h"
#include "DecorCircle.h"

CloudStrip::CloudStrip() {}//CloudStrip is an object with no collision that renders a simple box

void CloudStrip::Init(double y, double z, double boundX, int RadiusRange, int RadiusMin, int R, int G, int B)
{
	Object::Init(0, y, z, boundX, RadiusMin+RadiusRange, 0, 0, 0, 0, 0, 0, 0, 0);

	CloudStrip::R = R;//color of box
	CloudStrip::G = G;
	CloudStrip::B = B;

	for (int a = 0; a < boundX; a++) {
		if (rand() % 100 == 1) {
			DecorCircle *CloudPiece = new DecorCircle();
			int Radius = rand() % RadiusRange + RadiusMin;
			CloudPiece->Init(a, y + Radius, z, Radius, R, G, B, false);
			AllObjectsList.push_back(CloudPiece);
		}
	}
}

void CloudStrip::Update()
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
			(*iter)->Update();
	}
}

void CloudStrip::Render(double cameraXPos, double cameraYPos)
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
			(*iter)->Render(cameraXPos, cameraYPos);
	}
}