#include "Globals.h"
#include "IslandUnderside.h"
#include "DecorBox.h"
#include "DecorGirder.h"
#include "DecorFourSidedPolygon.h"
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;

IslandUnderside::IslandUnderside() {}

void IslandUnderside::Destroy() {}

void IslandUnderside::Init(double x, double y, double z, double boundX, double boundY)
{
	//in case these names make no sense:
	//Girders are the vertical shafts descending from the island.
	//Underside is the dark stone layer connecting the Struts and girders to the actual island
	//Struts are the erratically placed bars running throught the girders, connecting them to each other, as well as the Island.

	Object::Init(x, y, z);

	int GirderBoundX = 50;//dimensions of girder
	int GirderBoundY = 750;
	int GirderSideWidth = 12;
	int GirderCrossSize = 18;//thickness of crosses and Horizontal bars on Girder
	int GirderCrossNum = 2;//number of crosses created before a horizontal bar is used, and the pattern repeats

	int GirderCrossBoundX = 25;
	int GirderCrossBoundY = 65;

	int GirderPlacingMinimum = 60;//minimum distance from center
	int GirderPlacingRange = 30;//range to max distance from center
	int GirderDistanceFromCenter = rand() % GirderPlacingRange + GirderPlacingMinimum;

	int UndersideSectionNum = 7;//number of stone sections on underside
	int UndersideRange = 75;
	int UndersideMinimum = 100;
	int UndersideColorRange = 25;
	int UndersideColorMinimum = 65;

	int GirderFrameR = 127;//deep brown-red
	int GirderFrameG = 65;
	int GirderFrameB = 48;

	int StrutR = 165;//brown-grey. also used in girder cross.
	int StrutG = 142;
	int StrutB = 129;

	int PlateColorRange = 50;//colors of plates involved in connecting Struts to Girders and other Struts
	int PlateColorMinimum = 105;

	int PlateBoundMinimum = 25;//dimensions of plates
	int PlateBoundRange = 15;
	int PlateBoundX = rand() % PlateBoundRange + PlateBoundMinimum;
	int PlateBoundY = rand() % PlateBoundRange + PlateBoundMinimum;

	//Girders
	DecorGirder *LeftGirder = new DecorGirder();
	DecorGirder *RightGirder = new DecorGirder();

	LeftGirder->Init((x + boundX / 2) - GirderDistanceFromCenter - GirderBoundX, y, GirderBoundX, GirderBoundY, GirderSideWidth, GirderCrossSize, GirderCrossBoundX, GirderCrossBoundY, GirderCrossNum, StrutR, StrutG, StrutB, GirderFrameR, GirderFrameG, GirderFrameB);
	RightGirder->Init((x + boundX / 2) + GirderDistanceFromCenter, y, GirderBoundX, GirderBoundY, GirderSideWidth, GirderCrossSize, GirderCrossBoundX, GirderCrossBoundY, GirderCrossNum, StrutR, StrutG, StrutB, GirderFrameR, GirderFrameG, GirderFrameB);

	AllObjectsList.push_back(LeftGirder);
	AllObjectsList.push_back(RightGirder);

	//Supports	
	//Underside to Left Girder	
	/*
	int StrutSizeW = rand()%10+10;//width of strut

	int int_boundX = boundX;//for rand() function purposes (requires conversion to int)
	int LeftStrutX = rand() % (-(GirderDistanceFromCenter+GirderBoundX + StrutSizeW) + (int_boundX / 2)) + x;
	int LeftStrutY = rand() % (GirderBoundY / 2) + (y + GirderBoundY / 10);
	DecorFourSidedPolygon *LeftStrut = new DecorFourSidedPolygon();
	LeftStrut->Init(
		LeftStrutX, y,
		LeftStrutX - StrutSizeW, y,		
		(x + boundX / 2) - GirderDistanceFromCenter - GirderBoundX, LeftStrutY, 
		(x + boundX / 2) - GirderDistanceFromCenter - GirderBoundX - StrutSizeW, LeftStrutY,		
		StrutR, StrutG, StrutB);
	AllObjectsList.push_back(LeftStrut);

	//RightGirder to Underside
	int RightStrutX = rand() % (int_boundX/2 - (GirderDistanceFromCenter+GirderBoundX + StrutSizeW)) + (x + (int_boundX / 2) + GirderDistanceFromCenter + GirderBoundX);
	int RightStrutY = rand() % (GirderBoundY / 2) + (y+GirderBoundY/10);
	DecorFourSidedPolygon *RightStrut = new DecorFourSidedPolygon();
	RightStrut->Init(
		(x + boundX / 2) + GirderDistanceFromCenter + GirderBoundX + StrutSizeW, RightStrutY,
		(x + boundX / 2) + GirderDistanceFromCenter + GirderBoundX, RightStrutY,
		
		RightStrutX, y,
		RightStrutX - StrutSizeW, y,		
		StrutR, StrutG, StrutB);
	AllObjectsList.push_back(RightStrut);

	//Connections
	*/

	//Underside
	/*for(int a = 0; a < UndersideSectionNum; a++) {
		int UndersideColor = rand() % UndersideColorRange + UndersideColorMinimum;
		DecorBox *CliffWall = new DecorBox();
		CliffWall->Init(x + (boundX/UndersideSectionNum)*a, y, 0, boundX/UndersideSectionNum, rand() % UndersideRange + UndersideMinimum, UndersideColor, UndersideColor, UndersideColor);
		AllObjectsList.push_back(CliffWall);
	}*/
}

//===========================================================================================================================================================================================================================
//OBJECT LIST MANAGEMENT
//===========================================================================================================================================================================================================================

void IslandUnderside::Update()
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
		(*iter)->Update();
	}
}

void IslandUnderside::Render(double cameraXPos, double cameraYPos)
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
		(*iter)->Render(cameraXPos, cameraYPos);
	}
}

void IslandUnderside::ObjectCollision()
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

void IslandUnderside::ObjectDeletion()
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