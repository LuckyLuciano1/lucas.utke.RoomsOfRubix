#include "Globals.h"
#include "Island.h"
#include "Player.h"
#include "DecorBox.h"
#include "DecorCircle.h"
#include "DecorFourSidedPolygon.h"
#include "DecorGirder.h"
#include "IslandUnderside.h"
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;

bool compare(Object *L1, Object *L2);//function for sorting values. not part of the Island class, merely inhabits same file

Island::Island() {}

void Island::Destroy() {}

void Island::Init(Player *player, int ID, double IslandX, double IslandY, int IslandBoundX, int IslandBoundY)
{
	Island::ID = ID;

	Island::IslandX = IslandX;
	Island::IslandY = IslandY;
	Island::IslandBoundX = IslandBoundX;
	Island::IslandBoundY = IslandBoundY;

	//AllObjectsList.push_back(player);
	bool OnScreen = false;
	
	//generating Underside of Island
	IslandUnderside *islandunderside = new IslandUnderside();
	islandunderside->Init(IslandX, IslandY + IslandBoundY, IslandBoundX, 750);
	islandunderside->SetVerticality(HORIZONTAL);
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
	Underside->SetVerticality(HORIZONTAL);
	Base->SetVerticality(HORIZONTAL);

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
			//ProtBase->SetVerticality(HORIZONTAL);
			ProtUnderside->Init(position + IslandX, IslandY + IslandBoundY + BorderSize + BoundY, 0, BoundX, rand() % UndersideSizeRange + MinimumUndersideSize, UndersideR, UndersideG, UndersideB);

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
			//ProtBase->SetVerticality(HORIZONTAL);

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
			//ProtBase->SetVerticality(HORIZONTAL);
			ProtUnderside->Init(IslandX - BorderSize - BoundX, position + IslandY + BoundY, 0, BoundX, UndersideSize, UndersideR, UndersideG, UndersideB);

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
			//ProtBase->SetVerticality(HORIZONTAL);
			ProtUnderside->Init(IslandX + IslandBoundX + BorderSize, position + IslandY + BoundY, 0, BoundX, UndersideSize, UndersideR, UndersideG, UndersideB);

			AllObjectsList.push_back(ProtBase);
			AllObjectsList.push_back(ProtUnderside);

			AreaRemaining -= BoundY + position + UndersideSize;
		}
	}
	//insert later microenvironment creation here

}

//===========================================================================================================================================================================================================================
//OBJECT LIST MANAGEMENT
//===========================================================================================================================================================================================================================

void Island::ObjectUpdate()
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
		(*iter)->Update();
	}
}

void Island::ObjectRender(double cameraXPos, double cameraYPos)
{
	//al_draw_filled_rectangle(IslandX+cameraXPos, IslandY+cameraYPos, IslandX + IslandBoundX+cameraXPos, IslandY + IslandBoundY+cameraYPos, al_map_rgb(174, 178, 95));//displaying area of island (for testing purposes)
	sort(AllObjectsList.begin(), AllObjectsList.end(), compare);

	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
		(*iter)->Render(cameraXPos, cameraYPos);
	}
}

void Island::ObjectCollision()
{
	/*for (citer = ObjectCollisionList.begin(); citer != ObjectCollisionList.end(); ++citer)
	{
		for (citer2 = citer; citer2 != ObjectCollisionList.end(); ++citer2)
		{
			if ((*citer)->CollisionCheck((*citer2)))
			{
				(*citer)->Collided((*citer2));
				(*citer2)->Collided((*citer));
			}
		}
	}*/
}

void Island::ObjectDeletion()
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end();)
	{
		if (!(*iter)->GetValid())
		{
			delete (*iter);
			iter = AllObjectsList.erase(iter);
		}
		else
			iter++;
	}
}

void Island::CreateNorthPath(int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount) {

	int counter = PathFrequency - 1;
	for (int a = 0; a < IslandBoundY / 2; a++) {
		counter++;
		if (counter == PathFrequency) {//chance of spawning a circle path
			counter = 0;
			for (int b = 0; b < CircleAmount; b++) {
				int CircleRadius = rand() % CircleSizeRange + MinimumCircleSize;

				if (IslandY + IslandBoundY / 2 - a - CircleRadius > IslandY) {//checking whether circle will beyond bounds of island
					int CircleColor = rand() % CircleColorRange + MinimumCircleColor;

					DecorCircle *PathPiece = new DecorCircle();
					PathPiece->Init(IslandX + IslandBoundX / 2 + (rand() % PathWideness * 2 - PathWideness), IslandY + IslandBoundY / 2 - a, 0, CircleRadius, CircleColor, CircleColor, CircleColor, false);
					AllObjectsList.push_back(PathPiece);
					PathPiece->SetVerticality(HORIZONTAL);
				}
			}
		}
	}
}
void Island::CreateSouthPath(int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount) {

	int counter = PathFrequency - 1;
	for (int a = 0; a < IslandBoundY / 2; a++) {
		counter++;
		if (counter == PathFrequency) {
			counter = 0;
			for (int b = 0; b<CircleAmount; b++) {
				int CircleRadius = rand() % CircleSizeRange + MinimumCircleSize;

				if (IslandY + IslandBoundY / 2 + a + CircleRadius < IslandY + IslandBoundY) {//checking whether circle will beyond bounds of island
					int CircleColor = rand() % CircleColorRange + MinimumCircleColor;

					DecorCircle *PathPiece = new DecorCircle();
					PathPiece->Init(IslandX + IslandBoundX / 2 + (rand() % PathWideness * 2 - PathWideness), IslandY + IslandBoundY / 2 + a, 0, CircleRadius, CircleColor, CircleColor, CircleColor, false);
					AllObjectsList.push_back(PathPiece);
					PathPiece->SetVerticality(HORIZONTAL);
				}
			}
		}
	}
}
void  Island::CreateWestPath(int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount) {

	int counter = PathFrequency - 1;
	for (int a = 0; a < IslandBoundX / 2; a++) {
		counter++;
		if (counter == PathFrequency) {
			counter = 0;
			for (int b = 0; b<CircleAmount; b++) {
				int CircleRadius = rand() % CircleSizeRange + MinimumCircleSize;

				if (IslandX + IslandBoundX / 2 - a - CircleRadius > IslandX) {//checking whether circle will beyond bounds of island
					int CircleColor = rand() % CircleColorRange + MinimumCircleColor;

					DecorCircle *PathPiece = new DecorCircle();
					PathPiece->Init(IslandX + IslandBoundX / 2 - a, IslandY + IslandBoundY / 2 + (rand() % PathWideness * 2 - PathWideness), 0, CircleRadius, CircleColor, CircleColor, CircleColor, false);
					AllObjectsList.push_back(PathPiece);
					PathPiece->SetVerticality(HORIZONTAL);
				}
			}
		}
	}
}
void  Island::CreateEastPath(int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount) {
	
	int counter = PathFrequency - 1;
	for (int a = 0; a < IslandBoundX / 2; a++) {
		counter++;
		if (counter == PathFrequency) {
			counter = 0;
			for (int b = 0; b<CircleAmount; b++) {
				int CircleRadius = rand() % CircleSizeRange + MinimumCircleSize;

				if (IslandX + IslandBoundX / 2 + a + CircleRadius < IslandX + IslandBoundX) {//checking whether circle will beyond bounds of island
					int CircleColor = rand() % CircleColorRange + MinimumCircleColor;

					DecorCircle *PathPiece = new DecorCircle();
					PathPiece->Init(IslandX + IslandBoundX / 2 + a, IslandY + IslandBoundY / 2 + (rand() % PathWideness * 2 - PathWideness), 0, CircleRadius, CircleColor, CircleColor, CircleColor, false);
					AllObjectsList.push_back(PathPiece);
					PathPiece->SetVerticality(HORIZONTAL);
				}
			}
		}
	}
}

bool compare(Object *L1, Object *L2) {

	//primary condition, y position of base
	if ((*L1).GetVerticality() == HORIZONTAL && (*L2).GetVerticality() == HORIZONTAL) {//HORIZONTAL involved because some objects are supposed to be horizontal, so cannot include the base to properly render
		if ((*L1).GetY() < (*L2).GetY()) return true;
		if ((*L2).GetY() < (*L1).GetY()) return false;
	}
	else if ((*L1).GetVerticality() == HORIZONTAL) {
		if ((*L1).GetY() < (*L2).GetY() + (*L2).GetBoundY()) return true;
		if ((*L2).GetY() + (*L2).GetBoundY() < (*L1).GetY()) return false;
	}
	else if ((*L2).GetVerticality() == HORIZONTAL) {
		if ((*L1).GetY() + (*L1).GetBoundY() < (*L2).GetY()) return true;
		if ((*L2).GetY() < (*L1).GetY() + (*L1).GetBoundY()) return false;
	}
	else {//two vertical objects being compared
		if ((*L1).GetY() + (*L1).GetBoundY() < (*L2).GetY() + (*L2).GetBoundY()) return true;
		if ((*L2).GetY() + (*L2).GetBoundY() < (*L1).GetY() + (*L1).GetBoundY()) return false;
	}
	//secondary condition, depth
	if ((*L1).GetZ() > (*L2).GetZ()) return true;
	if ((*L2).GetZ() > (*L1).GetZ()) return false;

	return false;
}