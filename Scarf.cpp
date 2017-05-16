#include "Scarf.h"
#include "ScarfPiece.h"
#define PI 3.14159265
#define DEGREES(x) int((x)/360.0*0xFFFFFF)
#define RADIANS(x) int((x)/2/M_PI*0xFFFFFF)

Scarf::Scarf() {}

void Scarf::Init(double x, double y, double z, int ScarfPieceNum)
{
	Object::x = x;
	Object::y = y;
	Object::z = z;
	Scarf::ScarfPieceNum = ScarfPieceNum;

}

void Scarf::Update()
{
	Object::Update();
}