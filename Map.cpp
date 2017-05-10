#include "Map.h"
#include "Globals.h"
#include "Room.h"
#include <math.h>
#include <iostream>
#include <algorithm>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

Map::Map() {};

void Map::Destroy() {}

void Map::Init(ALLEGRO_BITMAP *MapImage, ALLEGRO_FONT *font) {
	Map::MapImage = MapImage;
	Map::font = font;
	ForeLayerX = SCREENW / 2;
	MidLayerX = SCREENW / 2;
	BackLayerX = SCREENW / 2;

	ForeLayerY = SCREENH / 2;
	MidLayerY = SCREENH / 2;
	BackLayerY = SCREENH / 2;

	

	TileBoundX = 50;
	TileBoundY = 50;

	TileSpacing = (TileBoundX + TileBoundY)/2;
	LayerSpacing = 25;
}

void Map::Render(char(&RoomMatrix)[3][3][3]) {

	for (int z = 0; z < 3 * TileSpacing; z += TileSpacing) {
	for (int x = 0; x < 3 * TileSpacing; x += TileSpacing) {
		for (int y = 0; y < 3 * TileSpacing; y += TileSpacing) {
			
				if (z == 0) {
					al_draw_tinted_scaled_rotated_bitmap_region(MapImage, 0, 0, TileBoundX, TileBoundY, al_map_rgba_f(1, 1, 1, 1), TileBoundX / 2, TileBoundY / 2, x + BackLayerX, y + BackLayerY, 1, 1, 0, 0);
					//al_draw_tinted_scaled_rotated_bitmap_region(image, imageX, imageY, imageboundX, imageboundY, transparency, boundX / 2, boundY / 2, x + cameraXPos, y + z + cameraYPos, boundX / imageboundX, boundY / imageboundY, angle, FlipHorizontal);
					al_draw_textf(font, al_map_rgb(255, 255, 255), x + BackLayerX, y + BackLayerY, 0, "%c", RoomMatrix[x/TileSpacing][y / TileSpacing][z / TileSpacing]);
				}
				else if (z == TileSpacing) {
					al_draw_tinted_scaled_rotated_bitmap_region(MapImage, 0, 0, TileBoundX, TileBoundY, al_map_rgba_f(1, 1, 1, 1), TileBoundX / 2, TileBoundY / 2, x + MidLayerX, y + MidLayerY, 1, 1, 0, 0);
					//al_draw_tinted_scaled_rotated_bitmap_region(image, imageX, imageY, imageboundX, imageboundY, transparency, boundX / 2, boundY / 2, x + cameraXPos, y + z + cameraYPos, boundX / imageboundX, boundY / imageboundY, angle, FlipHorizontal);
					al_draw_textf(font, al_map_rgb(255, 255, 255), x + MidLayerX, y + MidLayerY, 0, "%c", RoomMatrix[x / TileSpacing][y / TileSpacing][z / TileSpacing]);
				}
				else if (z == TileSpacing * 2) {
					al_draw_tinted_scaled_rotated_bitmap_region(MapImage, 0, 0, TileBoundX, TileBoundY, al_map_rgba_f(1, 1, 1, 1), TileBoundX / 2, TileBoundY / 2, x + ForeLayerX, y + ForeLayerY, 1, 1, 0, 0);
					//al_draw_tinted_scaled_rotated_bitmap_region(image, imageX, imageY, imageboundX, imageboundY, transparency, boundX / 2, boundY / 2, x + cameraXPos, y + z + cameraYPos, boundX / imageboundX, boundY / imageboundY, angle, FlipHorizontal);
					al_draw_textf(font, al_map_rgb(255, 255, 255), x + ForeLayerX, y + ForeLayerY, 0, "%c", RoomMatrix[x / TileSpacing][y / TileSpacing][z / TileSpacing]);
				}
				else
					cout << "LETTER DISPLAY ERROR FOR MAP" << endl;
			}
		}
	}
}

void Map::Update() {
	//MidLayer will not move. Fore and Back layers will mirror each other.

	if (MidLayerX - ForeLayerX < LayerSpacing)
		ForeLayerX--;

	if (ForeLayerY - MidLayerY < LayerSpacing)
		ForeLayerY++;


	if (BackLayerX - ForeLayerX < LayerSpacing*2)
		BackLayerX++;

	if (ForeLayerY - BackLayerY < LayerSpacing*2)
		BackLayerY--;
}
