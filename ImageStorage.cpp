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
	TerrainImage = al_load_bitmap("TerrainImage.png");
}