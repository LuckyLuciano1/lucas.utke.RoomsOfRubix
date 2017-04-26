#pragma once

#include <iostream>
#include "Globals.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>

using namespace std;

class ImageStorage
{
protected:
	ALLEGRO_BITMAP *PlayerImage;
	ALLEGRO_BITMAP *TerrainImage;
public:

	ImageStorage();
	void virtual Destroy();
	void Init();

	//==============================================
	//IMAGE ACCESS
	//==============================================
	ALLEGRO_BITMAP *GetPlayerImage() { return PlayerImage; }
	ALLEGRO_BITMAP *GetTerrainImage() { return TerrainImage; }
};
