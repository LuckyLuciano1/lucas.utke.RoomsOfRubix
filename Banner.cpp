#include "Banner.h"
#include "String.h"
Banner::Banner() {}

void Banner::Init(ALLEGRO_BITMAP *BannerImage, double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY)
{
	Object::Init(x, y, z, TILEW, TILEH*3, imageX, imageY, imageboundX, imageboundY, x+(TILEW/2), y, 5, TILEH*3);
	SetAnimating(false);
	Object::image = BannerImage;

	string->Init(x, y, 20, 10, 100, 20);//creating the Banner within the holder
}

void Banner::Render(double cameraXPos, double cameraYPos)
{
	
	Object::Render(cameraXPos, cameraYPos);
	
	//string->Update(x + cameraXPos - boundX / 2, y + z + cameraYPos - boundY/2, 0, 0);
	string->Update(x, y + z-12, 0, 0, cameraXPos, cameraYPos);
}

void Banner::Update()
{
	Object::Update();
}