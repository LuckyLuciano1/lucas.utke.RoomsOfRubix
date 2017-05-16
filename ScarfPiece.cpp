#include "Scarf.h"
#include "ScarfPiece.h"
#define PI 3.14159265
#define DEGREES(x) int((x)/360.0*0xFFFFFF)
#define RADIANS(x) int((x)/2/M_PI*0xFFFFFF)

ScarfPiece::ScarfPiece() {}

void ScarfPiece::Init(double Objx, double Objy, double Objz)
{
	ScarfPiece::ObjX = ObjX;
	ScarfPiece::ObjY = ObjY;
	ScarfPiece::ObjZ = ObjZ;
}

void ScarfPiece::Update(double dirX, double dirY, double dirZ)
{
	//Object::Update();
}

//cameraXDir = ((cameraXPos + cameraXDir) + ((object->GetX() - (SCREENW / 2)) + object->GetDirX())) / 25;//velocity of camera is dependent on distance from object
//cameraYDir = ((cameraYPos + cameraYDir) + ((object->GetY() - (SCREENH / 2)) + object->GetDirY())) / 25;

//cameraXPos -= cameraXDir;
//cameraYPos -= cameraYDir;