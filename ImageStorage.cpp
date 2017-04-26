#include "Globals.h"
#include "ImageStorage.h"
#include "Player.h"
#include "Tile.h"
#include <math.h>
#include <iostream>
using namespace std;

ImageStorage::ImageStorage() {}

void ImageStorage::Destroy() {}

void ImageStorage::Init()
{
	PlayerImage = al_load_bitmap("PlayerImage.png");
	al_convert_mask_to_alpha(PlayerImage, al_map_rgb(255, 255, 255));
	
	TerrainImage = al_load_bitmap("TerrainImage.png");
	al_convert_mask_to_alpha(TerrainImage, al_map_rgb(255, 255, 255));
}