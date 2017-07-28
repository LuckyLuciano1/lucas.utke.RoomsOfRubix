#include "Banner.h"
#include "String.h"
Banner::Banner() {}

void Banner::Init(double x, double y, double z)
{
	Object::Init(x, y, z);
	string->Init(x, y, 20, 10, 100, 20);//creating the Banner within the holder
}

void Banner::Render(double cameraXPos, double cameraYPos)
{
	//string->Update(x + cameraXPos - boundX / 2, y + z + cameraYPos - boundY/2, 0, 0);
	string->Update(x, y + z-12, 0, 0, cameraXPos, cameraYPos);
}

void Banner::Update()
{
	Object::Update();
}