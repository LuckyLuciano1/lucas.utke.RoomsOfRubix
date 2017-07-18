#pragma once

#include <iostream>
#include "Globals.h"
#include "Object.h"
#include "Player.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>

using namespace std;

class Island
{
private:

	double IslandX;//size and position of island
	double IslandY;
	int IslandBoundX;
	int IslandBoundY;

	bool OnScreen;//tracks whether island is on screen or not. if it is, Level class will use island lists in updating, rendering, etc.
	int ID;//rudimentary means of tracking which Island is which in-level.

	vector<Object*> AllObjectsList;//list that keeps track of all objects within each Island. Used for render, updating, collision, etc.
	vector<Object*>::iterator iter;

protected:

public:

	Island();
	void virtual Destroy();
	void Init(Player *player, int ID, double IslandX, double IslandY, int IslandBoundX, int IslandBoundY);

	//==============================================
	//POSITION/SCALE MANAGEMENT
	//==============================================
	int GetIslandX() { return IslandX; }
	int GetIslandY() { return IslandY; }

	void SetIslandX(int IslandX) { Island::IslandX = IslandX; }
	void SetIslandY(int IslandY) { Island::IslandY = IslandY; }

	int GetIslandBoundX() { return IslandBoundX; }
	int GetIslandBoundY() { return IslandBoundY; }

	void SetIslandBoundX(int IslandBoundX) { Island::IslandBoundX = IslandBoundX; }
	void SetIslandBoundY(int IslandBoundY) { Island::IslandBoundY = IslandBoundY; }


	//==============================================
	//OBJECT LIST MANAGEMENT
	//==============================================
	void ObjectUpdate();
	void ObjectRender(double cameraXPos, double cameraYPos);
	void ObjectCollision();
	void ObjectDeletion();

	//==============================================
	//MISC
	//==============================================
	bool GetOnScreen() { return OnScreen; }
	void SetOnScreen(bool OnScreen) { Island::OnScreen = OnScreen; }

	int GetID() { return ID; }
	void SetID(int ID) { Island::ID = ID; }

	void CreateNorthPath(int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount);
	void CreateSouthPath(int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount);
	void CreateWestPath(int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount);
	void CreateEastPath(int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount);
};