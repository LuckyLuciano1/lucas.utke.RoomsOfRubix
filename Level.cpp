#include "Globals.h"
#include "Level.h"
#include "Player.h"
#include "Tile.h"
#include "Banner.h"
#include "Grass.h"
#include "Camera.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include "String.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

Level::Level() {}

void Level::Destroy() {}

void Level::Init(char ID, int x, int y, int z, Player *player, Camera *camera, ALLEGRO_BITMAP *TerrainImage, ALLEGRO_FONT *font18)
{
	Level::ID = ID;
	Level::x = x;
	Level::y = y;
	Level::z = z;

	Level::font18 = font18;

	Level::camera = camera;
	Level::player = player;

	paused = false;

	enum BRIDGETYPE { EMPTY, ISLAND, CONNECTED_ISLAND, VERT_BRIDGE, HORIZ_BRIDGE };
	int IslandMatrix[5][5] = {
	ISLAND, EMPTY, ISLAND, EMPTY, ISLAND,
	EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
	ISLAND, EMPTY, ISLAND, EMPTY, ISLAND,
	EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
	ISLAND, EMPTY, ISLAND, EMPTY, ISLAND };

	//bridge logic here
	int CurrentX = 2 * (rand() % 3);//current position of Island being used to designate next bridge
	int CurrentY = 2 * (rand() % 3);
	bool PathEnd = false;

	bool PossiblePaths[4]{ true, true, true, true };//paths available for bridge. narrowed down based on location, then chosen based on for loop random number generator.
	enum PATHTRANSLATION { UP, DOWN, LEFT, RIGHT };

	while (PathEnd != true) {

		//narrowing down which direction it is possible to go in
		if (CurrentX - 1 < 0)//if at side/corner of map
			PossiblePaths[LEFT] = false;
		else {
			if (IslandMatrix[CurrentX - 2][CurrentY] == CONNECTED_ISLAND)//if adjacent island has already been connected
				PossiblePaths[LEFT] = false;
		}
		if (CurrentX + 1 > 4)
			PossiblePaths[RIGHT] = false;
		else {
			if (IslandMatrix[CurrentX + 2][CurrentY] == CONNECTED_ISLAND)
				PossiblePaths[RIGHT] = false;
		}
		if (CurrentY - 1 < 0)
			PossiblePaths[UP] = false;
		else {
			if (IslandMatrix[CurrentX][CurrentY - 2] == CONNECTED_ISLAND)
				PossiblePaths[UP] = false;
		}
		if (CurrentY + 1 > 4)
			PossiblePaths[DOWN] = false;
		else {
			if (IslandMatrix[CurrentX][CurrentY + 2] == CONNECTED_ISLAND)
				PossiblePaths[DOWN] = false;
		}
		//if no paths are available, end of path
		bool PathCheck = false;
		for (int a = 0; a < 4; a++) {
			if (PossiblePaths[a] == true)
				PathCheck = true;
		}
		if (PathCheck == false)
			PathEnd = true;


		if (PathEnd != true) {
			//picking direction from narrowed possibilities
			bool DonePicking = false;
			int ChosenPath = 0;

			while (DonePicking != true) {
				ChosenPath = rand() % 4;
				if (PossiblePaths[ChosenPath] == true) {
					DonePicking = true;
				}
			}

			IslandMatrix[CurrentX][CurrentY] = CONNECTED_ISLAND;//setting current island as connected

			//modifying matrix based on chosen path
			if (ChosenPath == UP) {
				IslandMatrix[CurrentX][CurrentY - 1] = VERT_BRIDGE;
				IslandMatrix[CurrentX][CurrentY - 2] = CONNECTED_ISLAND;
				CurrentY -= 2;
			}
			else if (ChosenPath == DOWN) {
				IslandMatrix[CurrentX][CurrentY + 1] = VERT_BRIDGE;
				IslandMatrix[CurrentX][CurrentY + 2] = CONNECTED_ISLAND;
				CurrentY += 2;
			}
			else if (ChosenPath == LEFT) {
				IslandMatrix[CurrentX - 1][CurrentY] = HORIZ_BRIDGE;
				IslandMatrix[CurrentX - 2][CurrentY] = CONNECTED_ISLAND;
				CurrentX -= 2;
			}
			else if (ChosenPath == RIGHT) {
				IslandMatrix[CurrentX + 1][CurrentY] = HORIZ_BRIDGE;
				IslandMatrix[CurrentX + 2][CurrentY] = CONNECTED_ISLAND;
				CurrentX += 2;
			}		
		}
		for (int a = 0; a < 4; a++)
			PossiblePaths[a] = true;//resetting possible paths array for repeat of while loop
	}

	//connecting islands left out by path
	for (int a = 0; a < 5; a += 2) {
		for (int b = 0; b < 5; b += 2) {
			if (IslandMatrix[a][b] == ISLAND) {//(and not CONNECTED_ISLAND)
				//runs similar code as above, but connects this unconnected island to an adjacent island that is connected (and does not loop to create its own path)

				if (a - 1 < 0)//if at side/corner of map
					PossiblePaths[LEFT] = false;
				else {
					if (IslandMatrix[a - 2][b] == ISLAND)//if adjacent island is not connected to main path
						PossiblePaths[LEFT] = false;
				}
				if (a + 1 > 4)
					PossiblePaths[RIGHT] = false;
				else {
					if (IslandMatrix[a + 2][b] == ISLAND)
						PossiblePaths[RIGHT] = false;
				}
				if (b - 1 < 0)
					PossiblePaths[UP] = false;
				else {
					if (IslandMatrix[a][b - 2] == ISLAND)
						PossiblePaths[UP] = false;
				}
				if (b + 1 > 4)
					PossiblePaths[DOWN] = false;
				else {
					if (IslandMatrix[a][b + 2] == ISLAND)
						PossiblePaths[DOWN] = false;
				}

				//if no islands are available, delete current island
				bool PathCheck = false;
				for (int a = 0; a < 4; a++) {
					if (PossiblePaths[a] == true)
						PathCheck = true;
				}
				if (PathCheck == false)
					IslandMatrix[a][b] = EMPTY;
				else {
					//picking direction from narrowed possibilities
					bool DonePicking = false;
					int ChosenPath = 0;

					while (DonePicking != true) {
						ChosenPath = rand() % 4;
						if (PossiblePaths[ChosenPath] == true) {
							DonePicking = true;
						}
					}

					IslandMatrix[a][b] = CONNECTED_ISLAND;//setting current island as connected

					//modifying matrix based on chosen path
					if (ChosenPath == UP)
						IslandMatrix[a][b - 1] = VERT_BRIDGE;
					else if (ChosenPath == DOWN)
						IslandMatrix[a][b + 1] = VERT_BRIDGE;
					else if (ChosenPath == LEFT)
						IslandMatrix[a - 1][b] = HORIZ_BRIDGE;
					else if (ChosenPath == RIGHT)
						IslandMatrix[a + 1][b] = HORIZ_BRIDGE;
				}
			}
		}
	}
	//Island creation
	int PathFrequency = 30;
	int PathWideness = 20;//range in which circle can be spawned at left or right

	int MinimumCircleSize = 10;
	int CircleSizeRange = 10;

	int MinimumCircleColor = 90;
	int CircleColorRange = 70;

	int CircleAmount = 2;//number of circles generated with each spot on the path

	int counter = 0;
	for (int a = 0; a < 5; a += 2) {
		for (int b = 0; b < 5; b += 2) {
			counter++;
			if (IslandMatrix[a][b] == CONNECTED_ISLAND) {
				Island *island = new Island();
				island->Init(player, counter, a * 750, b * 750, 500, 500);
				IslandList.push_back(island);

				if (a != 0) {//creating paths that connect to bridges based on previously planned out matrix
					if (IslandMatrix[a - 1][b] == HORIZ_BRIDGE)
						island->CreateWestPath(PathFrequency, PathWideness, MinimumCircleSize, CircleSizeRange, MinimumCircleColor, CircleColorRange, CircleAmount);
				}
				if (a != 4) {
					if (IslandMatrix[a + 1][b] == HORIZ_BRIDGE)
						island->CreateEastPath(PathFrequency, PathWideness, MinimumCircleSize, CircleSizeRange, MinimumCircleColor, CircleColorRange, CircleAmount);
				}
				if (b != 0) {
					if (IslandMatrix[a][b - 1] == VERT_BRIDGE)
						island->CreateNorthPath(PathFrequency, PathWideness, MinimumCircleSize, CircleSizeRange, MinimumCircleColor, CircleColorRange, CircleAmount);
				}
				if (b != 4) {
					if (IslandMatrix[a][b + 1] == VERT_BRIDGE)
						island->CreateSouthPath(PathFrequency, PathWideness, MinimumCircleSize, CircleSizeRange, MinimumCircleColor, CircleColorRange, CircleAmount);
				}
			}
		}
	}

	for (iter = IslandList.begin(); iter != IslandList.end(); ++iter)//setting islands to OnScreen (temp)
	{
		(*iter)->SetOnScreen(true);
	}

}

//===========================================================================================================================================================================================================================
//OBJECT LIST MANAGEMENT
//===========================================================================================================================================================================================================================

void Level::ObjectUpdate()
{
	player->Update();
	//cout << player->GetX() << ", " << player->GetY() << endl;
	/*for (iter = IslandList.begin(); iter != IslandList.end(); ++iter)//checks whether islands are onscreen or not
	{
		double oX = camera->GetCameraXPos();
		double oY = camera->GetCameraYPos();

		double x = (*iter)->GetIslandX();
		double y = (*iter)->GetIslandY();

		int obX = SCREENW;
		int obY = SCREENH;

		double boundX = (*iter)->GetIslandBoundX();
		double boundY = (*iter)->GetIslandBoundY();

		//cout << "Island(s) ";

		if (x + boundX > oX &&//basic collision equation
			x < oX + obX &&
			y + boundY > oY &&
			y < oY + obY)
			(*iter)->SetOnScreen(true);// , cout << (*iter)->GetID() << ", ";
		else
			(*iter)->SetOnScreen(false);
		//cout << "are onscreen" << endl;
	}*/

	if (!paused) {
		for (iter = IslandList.begin(); iter != IslandList.end(); ++iter)
		{
			//cout << (*iter)->GetIslandX() << ", " << (*iter)->GetIslandY() << endl;
			if ((*iter)->GetOnScreen())
				(*iter)->ObjectUpdate();
		}
	}
}

void Level::ObjectRender(double cameraXPos, double cameraYPos)
{
	player->Render(cameraXPos, cameraYPos);
	for (iter = IslandList.begin(); iter != IslandList.end(); ++iter)
	{
		if ((*iter)->GetOnScreen())
			(*iter)->ObjectRender(cameraXPos, cameraYPos);
	}
}

void Level::ObjectCollision()
{
	for (iter = IslandList.begin(); iter != IslandList.end(); ++iter)
	{
		if ((*iter)->GetOnScreen())
			(*iter)->ObjectCollision();
	}
}

void Level::ObjectDeletion()
{
	for (iter = IslandList.begin(); iter != IslandList.end(); ++iter)
	{
		if ((*iter)->GetOnScreen())
			(*iter)->ObjectDeletion();
	}
}

//===========================================================================================================================================================================================================================
//SHUFFLING
//===========================================================================================================================================================================================================================

void Level::Shuffle(int shuffletype)
{

	if (shuffletype == 1)
		RedClockwise();
	else if (shuffletype == 2)
		RedCounterClockwise();
	else if (shuffletype == 3)
		WhiteClockwise();
	else if (shuffletype == 4)
		WhiteCounterClockwise();
	else if (shuffletype == 5)
		BlueClockwise();
	else if (shuffletype == 6)
		BlueCounterClockwise();
	else if (shuffletype == 7)
		YellowClockwise();
	else if (shuffletype == 8)
		YellowCounterClockwise();
	else if (shuffletype == 9)
		GreenClockwise();
	else if (shuffletype == 10)
		GreenCounterClockwise();
	else if (shuffletype == 11)
		OrangeClockwise();
	else if (shuffletype == 12)
		OrangeCounterClockwise();
	else
		cout << "ERROR - SHUFFLE NOT GENERATED" << endl;
}

void Level::RedClockwise()
{
	if (x == 0 && y == 0 && z == 0) {//A
		x = 2;//C
		y = 0;
		z = 0;
	}
	else if (x == 1 && y == 0 && z == 0) {//B
		x = 2;//F
		y = 1;
		z = 0;
	}
	else if (x == 2 && y == 0 && z == 0) {//C
		x = 2;//I
		y = 2;
		z = 0;
	}
	else if (x == 0 && y == 1 && z == 0) {//D
		x = 1;//B
		y = 0;
		z = 0;
	}
	else if (x == 1 && y == 1 && z == 0) {//E
		x = 1;//N/A
		y = 1;
		z = 0;
	}
	else if (x == 2 && y == 1 && z == 0) {//F
		x = 1;//H
		y = 2;
		z = 0;
	}
	else if (x == 0 && y == 2 && z == 0) {//G
		x = 0;//A
		y = 0;
		z = 0;
	}
	else if (x == 1 && y == 2 && z == 0) {//H
		x = 0;//D
		y = 1;
		z = 0;
	}
	else if (x == 2 && y == 2 && z == 0) {//I
		x = 0;//G
		y = 2;
		z = 0;
	}
	else
		cout << "ERROR - REDCLOCKWISE" << endl;
}
void Level::RedCounterClockwise()
{
	if (x == 0 && y == 0 && z == 0) {//A
		x = 0;//G
		y = 2;
		z = 0;
	}
	else if (x == 1 && y == 0 && z == 0) {//B
		x = 0;//D
		y = 1;
		z = 0;
	}
	else if (x == 2 && y == 0 && z == 0) {//C
		x = 0;//A
		y = 0;
		z = 0;
	}
	else if (x == 0 && y == 1 && z == 0) {//D
		x = 1;//H
		y = 2;
		z = 0;
	}
	else if (x == 1 && y == 1 && z == 0) {//E
		x = 1;//N/A
		y = 1;
		z = 0;
	}
	else if (x == 2 && y == 1 && z == 0) {//F
		x = 1;//B
		y = 0;
		z = 0;
	}
	else if (x == 0 && y == 2 && z == 0) {//G
		x = 2;//I
		y = 2;
		z = 0;
	}
	else if (x == 1 && y == 2 && z == 0) {//H
		x = 2;//F
		y = 1;
		z = 0;
	}
	else if (x == 2 && y == 2 && z == 0) {//I
		x = 2;//C
		y = 0;
		z = 0;
	}
	else
		cout << "ERROR - REDCOUNTERCLOCKWISE" << endl;
}

void Level::WhiteClockwise()
{
	if (x == 0 && y == 0 && z == 0) {//A
		x = 0;//G
		y = 2;
		z = 0;
	}
	else if (x == 0 && y == 0 && z == 1) {//D
		x = 0;//O
		y = 1;
		z = 2;
	}
	else if (x == 0 && y == 0 && z == 2) {//G
		x = 0;//X
		y = 2;
		z = 2;
	}
	else if (x == 0 && y == 1 && z == 0) {//J
		x = 0;//D
		y = 0;
		z = 1;
	}
	else if (x == 0 && y == 1 && z == 1) {//M
		x = 0;//N/A
		y = 1;
		z = 1;
	}
	else if (x == 0 && y == 1 && z == 2) {//O
		x = 0;//U
		y = 2;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 0) {//R
		x = 0;//A
		y = 0;
		z = 0;
	}
	else if (x == 0 && y == 2 && z == 1) {//U
		x = 0;//J
		y = 1;
		z = 0;
	}
	else if (x == 0 && y == 2 && z == 2) {//X
		x = 0;//R
		y = 2;
		z = 0;
	}
	else
		cout << "ERROR - WHITECLOCKWISE" << endl;
}
void Level::WhiteCounterClockwise()
{
	if (x == 0 && y == 0 && z == 0) {//A
		x = 0;//R
		y = 2;
		z = 0;
	}
	else if (x == 0 && y == 0 && z == 1) {//D
		x = 0;//J
		y = 1;
		z = 0;
	}
	else if (x == 0 && y == 0 && z == 2) {//G
		x = 0;//A
		y = 0;
		z = 0;
	}
	else if (x == 0 && y == 1 && z == 0) {//J
		x = 0;//U
		y = 2;
		z = 1;
	}
	else if (x == 0 && y == 1 && z == 1) {//M
		x = 0;//N/A
		y = 1;
		z = 1;
	}
	else if (x == 0 && y == 1 && z == 2) {//O
		x = 0;//D
		y = 0;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 0) {//R
		x = 0;//X
		y = 2;
		z = 2;
	}
	else if (x == 0 && y == 2 && z == 1) {//U
		x = 0;//O
		y = 1;
		z = 2;
	}
	else if (x == 0 && y == 2 && z == 2) {//X
		x = 0;//G
		y = 0;
		z = 2;
	}
	else
		cout << "ERROR - WHITECOUNTERCLOCKWISE" << endl;
}

void Level::BlueClockwise()
{
	if (x == 2 && y == 0 && z == 0) {//C
		x = 0;//A
		y = 0;
		z = 0;
	}
	else if (x == 1 && y == 0 && z == 0) {//B
		x = 0;//J
		y = 1;
		z = 0;
	}
	else if (x == 0 && y == 0 && z == 0) {//A
		x = 0;//R
		y = 2;
		z = 0;
	}
	else if (x == 2 && y == 1 && z == 0) {//L
		x = 1;//B
		y = 0;
		z = 0;
	}
	else if (x == 1 && y == 1 && z == 0) {//K
		x = 1;//N/A
		y = 1;
		z = 0;
	}
	else if (x == 0 && y == 1 && z == 0) {//J
		x = 1;//S
		y = 2;
		z = 0;
	}
	else if (x == 2 && y == 2 && z == 0) {//T
		x = 2;//C
		y = 0;
		z = 0;
	}
	else if (x == 1 && y == 2 && z == 0) {//S
		x = 2;//L
		y = 1;
		z = 0;
	}
	else if (x == 0 && y == 2 && z == 0) {//R
		x = 2;//T
		y = 2;
		z = 0;
	}
	else
		cout << "ERROR - BLUECLOCKWISE" << endl;
}
void Level::BlueCounterClockwise()
{
	if (x == 2 && y == 0 && z == 0) {//C
		x = 2;//T
		y = 2;
		z = 0;
	}
	else if (x == 1 && y == 0 && z == 0) {//B
		x = 2;//L
		y = 1;
		z = 0;
	}
	else if (x == 0 && y == 0 && z == 0) {//A
		x = 2;//C
		y = 0;
		z = 0;
	}
	else if (x == 2 && y == 1 && z == 0) {//L
		x = 1;//S
		y = 2;
		z = 0;
	}
	else if (x == 1 && y == 1 && z == 0) {//K
		x = 1;//N/A
		y = 1;
		z = 0;
	}
	else if (x == 0 && y == 1 && z == 0) {//J
		x = 1;//B
		y = 0;
		z = 0;
	}
	else if (x == 2 && y == 2 && z == 0) {//T
		x = 0;//R
		y = 2;
		z = 0;
	}
	else if (x == 1 && y == 2 && z == 0) {//S
		x = 0;//J
		y = 1;
		z = 0;
	}
	else if (x == 0 && y == 2 && z == 0) {//R
		x = 0;//A
		y = 0;
		z = 0;
	}
	else
		cout << "ERROR - BLUECOUNTERCLOCKWISE" << endl;
}

void Level::YellowClockwise()
{
	if (x == 2 && y == 0 && z == 2) {//I
		x = 2;//C
		y = 0;
		z = 0;
	}
	else if (x == 2 && y == 0 && z == 1) {//F
		x = 2;//L
		y = 1;
		z = 0;
	}
	else if (x == 2 && y == 0 && z == 0) {//C
		x = 2;//T
		y = 2;
		z = 0;
	}
	else if (x == 2 && y == 1 && z == 2) {//Q
		x = 2;//F
		y = 0;
		z = 2;
	}
	else if (x == 2 && y == 1 && z == 1) {//N
		x = 2;//N/A
		y = 1;
		z = 1;
	}
	else if (x == 2 && y == 1 && z == 0) {//L
		x = 2;//W
		y = 2;
		z = 1;
	}
	else if (x == 2 && y == 2 && z == 2) {//Z
		x = 2;//I
		y = 0;
		z = 2;
	}
	else if (x == 2 && y == 2 && z == 1) {//W
		x = 2;//Q
		y = 1;
		z = 2;
	}
	else if (x == 2 && y == 2 && z == 0) {//T
		x = 2;//Z
		y = 2;
		z = 2;
	}
	else
		cout << "ERROR - YELLOWCLOCKWISE" << endl;
}
void Level::YellowCounterClockwise()
{
	if (x == 2 && y == 0 && z == 2) {//I
		x = 2;//Z
		y = 2;
		z = 2;
	}
	else if (x == 2 && y == 0 && z == 1) {//F
		x = 2;//Q
		y = 1;
		z = 2;
	}
	else if (x == 2 && y == 0 && z == 0) {//C
		x = 2;//I
		y = 0;
		z = 2;
	}
	else if (x == 2 && y == 1 && z == 2) {//Q
		x = 2;//W
		y = 2;
		z = 1;
	}
	else if (x == 2 && y == 1 && z == 1) {//N
		x = 2;//N/A
		y = 1;
		z = 1;
	}
	else if (x == 2 && y == 1 && z == 0) {//L
		x = 2;//F
		y = 0;
		z = 1;
	}
	else if (x == 2 && y == 2 && z == 2) {//Z
		x = 2;//T
		y = 2;
		z = 0;
	}
	else if (x == 2 && y == 2 && z == 1) {//W
		x = 2;//L
		y = 1;
		z = 0;
	}
	else if (x == 2 && y == 2 && z == 0) {//T
		x = 2;//C
		y = 0;
		z = 0;
	}
	else
		cout << "ERROR - YELLOWCOUNTERCLOCKWISE" << endl;
}

void Level::GreenClockwise()
{
	if (x == 0 && y == 0 && z == 2) {//G
		x = 0;//X
		y = 2;
		z = 2;
	}
	else if (x == 1 && y == 0 && z == 2) {//H
		x = 0;//O
		y = 1;
		z = 2;
	}
	else if (x == 2 && y == 0 && z == 2) {//I
		x = 0;//G
		y = 0;
		z = 2;
	}
	else if (x == 0 && y == 1 && z == 2) {//O
		x = 1;//Y
		y = 2;
		z = 2;
	}
	else if (x == 1 && y == 1 && z == 2) {//P
		x = 1;//N/A
		y = 1;
		z = 2;
	}
	else if (x == 2 && y == 1 && z == 2) {//Q
		x = 1;//H
		y = 0;
		z = 2;
	}
	else if (x == 0 && y == 2 && z == 2) {//X
		x = 2;//Z
		y = 2;
		z = 2;
	}
	else if (x == 1 && y == 2 && z == 2) {//Y
		x = 2;//Q
		y = 1;
		z = 2;
	}
	else if (x == 2 && y == 2 && z == 2) {//Z
		x = 2;//I
		y = 0;
		z = 2;
	}
	else
		cout << "ERROR - GREENCLOCKWISE" << endl;
}
void Level::GreenCounterClockwise()
{
	if (x == 0 && y == 0 && z == 2) {//G
		x = 2;//I
		y = 0;
		z = 2;
	}
	else if (x == 1 && y == 0 && z == 2) {//H
		x = 2;//Q
		y = 1;
		z = 2;
	}
	else if (x == 2 && y == 0 && z == 2) {//I
		x = 2;//Z
		y = 2;
		z = 2;
	}
	else if (x == 0 && y == 1 && z == 2) {//O
		x = 1;//H
		y = 0;
		z = 2;
	}
	else if (x == 1 && y == 1 && z == 2) {//P
		x = 1;//N/A
		y = 1;
		z = 2;
	}
	else if (x == 2 && y == 1 && z == 2) {//Q
		x = 1;//Y
		y = 2;
		z = 2;
	}
	else if (x == 0 && y == 2 && z == 2) {//X
		x = 0;//G
		y = 0;
		z = 2;
	}
	else if (x == 1 && y == 2 && z == 2) {//Y
		x = 0;//O
		y = 1;
		z = 2;
	}
	else if (x == 2 && y == 2 && z == 2) {//Z
		x = 0;//X
		y = 2;
		z = 2;
	}
	else
		cout << "ERROR - GREENCOUNTERCLOCKWISE" << endl;
}

void Level::OrangeClockwise()
{
	if (x == 2 && y == 2 && z == 0) {//T
		x = 2;//Z
		y = 2;
		z = 2;
	}
	else if (x == 1 && y == 2 && z == 0) {//S
		x = 2;//W
		y = 2;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 0) {//R
		x = 2;//T
		y = 2;
		z = 0;
	}
	else if (x == 2 && y == 2 && z == 1) {//W
		x = 1;//Y
		y = 2;
		z = 2;
	}
	else if (x == 1 && y == 2 && z == 1) {//V
		x = 1;//N/A
		y = 2;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 1) {//U
		x = 1;//S
		y = 2;
		z = 0;
	}
	else if (x == 2 && y == 2 && z == 2) {//Z
		x = 0;//X
		y = 2;
		z = 2;
	}
	else if (x == 1 && y == 2 && z == 2) {//Y
		x = 0;//U
		y = 2;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 2) {//X
		x = 0;//R
		y = 2;
		z = 0;
	}
	else
		cout << "ERROR - ORANGECLOCKWISE" << endl;
}
void Level::OrangeCounterClockwise()
{
	if (x == 2 && y == 2 && z == 0) {//T
		x = 0;//R
		y = 2;
		z = 0;
	}
	else if (x == 1 && y == 2 && z == 0) {//S
		x = 0;//U
		y = 2;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 0) {//R
		x = 0;//X
		y = 2;
		z = 2;
	}
	else if (x == 2 && y == 2 && z == 1) {//W
		x = 1;//S
		y = 2;
		z = 0;
	}
	else if (x == 1 && y == 2 && z == 1) {//V
		x = 1;//N/A
		y = 2;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 1) {//U
		x = 1;//Y
		y = 2;
		z = 2;
	}
	else if (x == 2 && y == 2 && z == 2) {//Z
		x = 2;//T
		y = 2;
		z = 0;
	}
	else if (x == 1 && y == 2 && z == 2) {//Y
		x = 2;//W
		y = 2;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 2) {//X
		x = 2;//Z
		y = 2;
		z = 2;
	}
	else
		cout << "ERROR - ORANGECOUNTERCLOCKWISE" << endl;
}