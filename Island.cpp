#include "Globals.h"
#include "Island.h"
#include "Player.h"
#include "Grass.h"
#include "DecorBox.h"
#include "DecorCircle.h"
#include "DecorFourSidedPolygon.h"
#include "DecorGirder.h"
#include "DecorPath.h"
#include "IslandUnderside.h"
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;

Island::Island() {}

void Island::Destroy() {}

void Island::Init(Player *player, int ID, double IslandX, double IslandY, int IslandBoundX, int IslandBoundY)
{
	Island::ID = ID;

	Island::IslandX = IslandX;
	Island::IslandY = IslandY;
	Island::IslandBoundX = IslandBoundX;
	Island::IslandBoundY = IslandBoundY;

	bool OnScreen = false;
	
	//generating Underside of Island
	IslandUnderside *islandunderside = new IslandUnderside();
	islandunderside->Init(IslandX, IslandY + IslandBoundY, IslandBoundX, IslandBoundX, 750);
	islandunderside->SetVerticality(VERTICAL);
	islandunderside->SetLayer(CLOUDLINE);
	AllObjectsList.push_back(islandunderside);

	//generating standard rim of Island
	int BorderSize = 8;
	int MinimumUndersideSize = 50;
	int UndersideSizeRange = 20;

	int BorderR = 157;
	int BorderG = 149;
	int BorderB = 119;

	int UndersideR = 135;
	int UndersideG = 128;
	int UndersideB = 94;

	DecorBox *Base = new DecorBox();//generating grass section of island
	DecorBox *Border = new DecorBox();//generating light gray border
	DecorBox *Underside = new DecorBox();//generating dark gray underside of border

	Border->Init(IslandX - BorderSize, IslandY - BorderSize, 0, IslandBoundX + (BorderSize * 2), IslandBoundY + (BorderSize * 2), BorderR, BorderG, BorderB);
	Underside->Init(IslandX - BorderSize, IslandY + IslandBoundY + BorderSize, 0, IslandBoundX + (BorderSize * 2), MinimumUndersideSize, UndersideR - 20, UndersideG - 20, UndersideB - 20);
	Base->Init(IslandX, IslandY, 0, IslandBoundX, IslandBoundY, 196, 187, 54);

	Border->SetVerticality(HORIZONTAL);
	Border->SetLayer(FOUNDATION);

	Underside->SetVerticality(HORIZONTAL);
	Underside->SetLayer(FOUNDATION);

	Base->SetVerticality(HORIZONTAL);
	Base->SetLayer(BASE);

	AllObjectsList.push_back(Border);
	AllObjectsList.push_back(Underside);
	AllObjectsList.push_back(Base);
	
	//generating background underside tiles at front of island (currently disabled)
	/*double BoxNum = rand() % 6 + 10;
	double position = 0;
	for (int a = 0; a < BoxNum; a++) {
		double BoundX = IslandBoundX / BoxNum;
		DecorBox *UndersideBack = new DecorBox();
		UndersideBack->Init(IslandX + position, IslandY+IslandBoundY+(BorderSize*5), 0, BoundX, rand()%100+100, 82, 82, 82);
		//UndersideBack->SetVerticality(HORIZONTAL);
		AllObjectsList.push_back(UndersideBack);
		position += BoundX;
	}*/

	//generating protrusions from rim
	
	double ProtNum = rand() % 2 + 10;//number of protrusions generated for each side
	int AreaRemaining = IslandBoundX + (BorderSize * 2);//area remaining on each side that can be used for generating a new protrusion

	int ProtrusionRange = 10;

	int ProtrusionWidthRange = 60;
	int MinimumProtrusionWidth = 30;

	for (int a = 0; a < ProtNum; a++) {//south side protrusions being generated
		int BoundX = rand() % ProtrusionWidthRange + MinimumProtrusionWidth;
		int BoundY = rand() % ProtrusionRange + (BorderSize);
		if (AreaRemaining > BoundX) {
			double position = (IslandBoundX - AreaRemaining) + (rand() % (AreaRemaining - BoundX))/2;

			DecorBox *ProtBase = new DecorBox();
			DecorBox *ProtUnderside = new DecorBox();

			ProtBase->Init(position + IslandX, IslandY + IslandBoundY + BorderSize, 0, BoundX, BoundY, BorderR, BorderG, BorderB);
			ProtBase->SetVerticality(HORIZONTAL);
			ProtBase->SetLayer(BASE);//cheating a little here. minor exception to layer system I created, and rather than create a whole new layer for one object, I figured I can just do this.

			ProtUnderside->Init(position + IslandX, IslandY + IslandBoundY + BorderSize + BoundY, 0, BoundX, rand() % UndersideSizeRange + MinimumUndersideSize, UndersideR, UndersideG, UndersideB);
			ProtUnderside->SetLayer(FOUNDATION);

			AllObjectsList.push_back(ProtBase);
			AllObjectsList.push_back(ProtUnderside);

			AreaRemaining -= BoundX + position;//updating area remaining for next protrusion to be generated
		}
	}

	ProtNum = rand() % 2 + 2;//refreshing necessary variables
	AreaRemaining = IslandBoundX + (BorderSize * 2);

	for (int a = 0; a < ProtNum; a++) {//north side protrusions being generated
		int BoundX = rand() % ProtrusionWidthRange + MinimumProtrusionWidth;
		int BoundY = rand() % ProtrusionRange + (BorderSize);
		if (AreaRemaining > BoundX) {
			double position = (IslandBoundX + (BorderSize * 2) - AreaRemaining) + (rand() % (AreaRemaining - BoundX))/2;

			DecorBox *ProtBase = new DecorBox();
			ProtBase->Init(position + IslandX, IslandY - BorderSize - BoundY, 0, BoundX, BoundY, BorderR, BorderG, BorderB);
			ProtBase->SetVerticality(HORIZONTAL);
			ProtBase->SetLayer(FOUNDATION);
			AllObjectsList.push_back(ProtBase);

			AreaRemaining -= BoundX + position;
		}
	}

	ProtNum = rand() % 2 + 2;
	AreaRemaining = IslandBoundY + (BorderSize * 2);

	for (int a = 0; a < ProtNum; a++) {//west side protrusions being generated
		int BoundX = rand() % ProtrusionRange + (BorderSize);
		int BoundY = rand() % ProtrusionWidthRange + MinimumProtrusionWidth;
		int UndersideSize = rand() % UndersideSizeRange + MinimumUndersideSize;
		if (AreaRemaining > BoundY + UndersideSize) {
			double position = (IslandBoundY - AreaRemaining) + (rand() % (AreaRemaining - BoundY - UndersideSize))/2;

			DecorBox *ProtBase = new DecorBox();
			DecorBox *ProtUnderside = new DecorBox();

			ProtBase->Init(IslandX - BorderSize - BoundX, position + IslandY, 0, BoundX, BoundY, BorderR, BorderG, BorderB);
			ProtBase->SetVerticality(HORIZONTAL);
			ProtBase->SetLayer(FOUNDATION);
			ProtUnderside->Init(IslandX - BorderSize - BoundX, position + IslandY + BoundY, 0, BoundX, UndersideSize, UndersideR, UndersideG, UndersideB);
			ProtUnderside->SetLayer(FOUNDATION);

			AllObjectsList.push_back(ProtBase);
			AllObjectsList.push_back(ProtUnderside);

			AreaRemaining -= BoundY + position + UndersideSize;
		}
	}

	ProtNum = rand() % 2 + 2;
	AreaRemaining = IslandBoundY + (BorderSize * 2);

	for (int a = 0; a < ProtNum; a++) {//east side protrusions being generated
		int BoundX = rand() % ProtrusionRange + (BorderSize);
		int BoundY = rand() % ProtrusionWidthRange + MinimumProtrusionWidth;
		int UndersideSize = rand() % UndersideSizeRange + MinimumUndersideSize;
		if (AreaRemaining > BoundY + UndersideSize) {
			double position = (IslandBoundY - AreaRemaining) + (rand() % (AreaRemaining - BoundY - UndersideSize))/2;

			DecorBox *ProtBase = new DecorBox();
			DecorBox *ProtUnderside = new DecorBox();

			ProtBase->Init(IslandX + IslandBoundX + BorderSize, position + IslandY, 0, BoundX, BoundY, BorderR, BorderG, BorderB);
			ProtBase->SetVerticality(HORIZONTAL);
			ProtBase->SetLayer(FOUNDATION);
			ProtUnderside->Init(IslandX + IslandBoundX + BorderSize, position + IslandY + BoundY, 0, BoundX, UndersideSize, UndersideR, UndersideG, UndersideB);
			ProtUnderside->SetLayer(FOUNDATION);

			AllObjectsList.push_back(ProtBase);
			AllObjectsList.push_back(ProtUnderside);

			AreaRemaining -= BoundY + position + UndersideSize;
		}
	}
	//insert later microenvironment creation here

	//generating grass
	for (int a = 0; a < IslandBoundX; a++) {
			if (rand() % 600 == 1) {
				Grass *grass = new Grass();
				grass->Init(IslandX + rand()%IslandBoundX, IslandY + rand()%IslandBoundY, 0, 10, 1, 10, 10);
				AllObjectsList.push_back(grass);
			}
	}


	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)//marks all created objects within island Init with island's ID, for level sorting purposes.
	{
		(*iter)->SetClusterID(ID);
	}
}

//===========================================================================================================================================================================================================================
//PATH CREATION
//===========================================================================================================================================================================================================================

void Island::CreateNorthPath(int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount) {
	DecorPath *Path = new DecorPath();
	Path->Init(IslandX, IslandY, IslandBoundX, IslandBoundY, PathFrequency, PathWideness, MinimumCircleSize, CircleSizeRange, MinimumCircleColor, CircleColorRange, CircleAmount, NORTH);
	Path->SetVerticality(HORIZONTAL);
	Path->SetClusterID(ID);
	Path->EnableSorting(PathWideness * 2, IslandBoundY / 2);

	AllObjectsList.push_back(Path);
}
void Island::CreateSouthPath(int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount) {
	DecorPath *Path = new DecorPath();
	Path->Init(IslandX, IslandY, IslandBoundX, IslandBoundY, PathFrequency, PathWideness, MinimumCircleSize, CircleSizeRange, MinimumCircleColor, CircleColorRange, CircleAmount, SOUTH);
	Path->SetVerticality(HORIZONTAL);
	Path->SetClusterID(ID);
	Path->EnableSorting(PathWideness * 2, IslandBoundY / 2);

	AllObjectsList.push_back(Path);
}
void  Island::CreateEastPath(int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount) {
	DecorPath *Path = new DecorPath();
	Path->Init(IslandX, IslandY, IslandBoundX, IslandBoundY, PathFrequency, PathWideness, MinimumCircleSize, CircleSizeRange, MinimumCircleColor, CircleColorRange, CircleAmount, EAST);
	Path->SetVerticality(HORIZONTAL);
	Path->SetClusterID(ID);
	Path->EnableSorting(IslandBoundX / 2, PathWideness * 2);

	AllObjectsList.push_back(Path);
}
void  Island::CreateWestPath(int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount) {

	DecorPath *Path = new DecorPath();
	Path->Init(IslandX, IslandY, IslandBoundX, IslandBoundY, PathFrequency, PathWideness, MinimumCircleSize, CircleSizeRange, MinimumCircleColor, CircleColorRange, CircleAmount, WEST);
	Path->SetVerticality(HORIZONTAL);
	Path->SetClusterID(ID);
	Path->EnableSorting(IslandBoundX / 2, PathWideness * 2);

	AllObjectsList.push_back(Path);
}