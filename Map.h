#pragma once

#include <iostream>
#include "Globals.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>

using namespace std;

class Map
{
private:
	ALLEGRO_BITMAP *MapImage;
	ALLEGRO_FONT *font;

	double ForeLayerX;
	double MidLayerX;
	double BackLayerX;

	double ForeLayerY;
	double MidLayerY;
	double BackLayerY;

	int TileSpacing;//spacing between room 'tiles' of map
	int LayerSpacing;//spacing between layers upon expansion

	int TileBoundX;
	int TileBoundY;
public:
	Map();
	void virtual Destroy();
	void Init(ALLEGRO_BITMAP *MapImage, ALLEGRO_FONT *font);
	void Render(char (&RoomMatrix)[3][3][3]);
	void Update();

	void ResetLayers() { //resets coordinates of layers to make sliding animation work when map is repeatedly activated
	ForeLayerX = SCREENW/2;
	MidLayerX = SCREENW/2;
	BackLayerX = SCREENW/2;
	ForeLayerY = SCREENH/2;
	MidLayerY = SCREENH/2;
	BackLayerY = SCREENH/2;	};
};