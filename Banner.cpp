#include "Banner.h"
#include "String.h"
Banner::Banner() {}

void Banner::Init(ALLEGRO_BITMAP *BannerImage, double x, double y, double z, int imageX, int imageY, double imageboundX, double imageboundY)
{
	Object::Init(x, y, z, TILEW, TILEH*3, imageX, imageY, imageboundX, imageboundY, x + (boundX/2), y + boundY, boundX / 2, 5);
	SetAnimating(false);
	Object::image = BannerImage;

	string->Init(x, y, 20, 10, 100, 20);//creating the Banner within the holder
}

void Banner::Render(double cameraXPos, double cameraYPos)
{
	
	Object::Render(cameraXPos, cameraYPos);
	
	//string->Update(x + cameraXPos - boundX / 2, y + z + cameraYPos - boundY/2, 0, 0);
	string->Update(x - 25, y + z - 90, 0, 0, cameraXPos, cameraYPos);
	al_draw_filled_rectangle(colX + cameraXPos, colY + cameraYPos + z, colX + cameraXPos + colboundX, colY + cameraYPos + colboundY + z, al_map_rgb(255, 0, 255));
}

void Banner::Update()
{
	Object::Update();
}