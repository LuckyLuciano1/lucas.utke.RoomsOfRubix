#include "Globals.h"
#include "Room.h"
#include "Player.h"
#include "Tile.h"
#include "Banner.h"
#include "Grass.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include "String.h"

using namespace std;

bool compare(Object *L1, Object *L2);//function for sorting values. not part of the room class, merely inhabits same file

Room::Room() {}

void Room::Destroy() {}

void Room::Init(char ID, int x, int y, int z, Player *player, ALLEGRO_BITMAP *TerrainImage)
{
	Room::ID = ID;
	Room::x = x;
	Room::y = y;
	Room::z = z;

	paused = false;

	AllObjects.push_back(player);
	ObjectCollisionList.push_back(player);

	LevelMatrix[LEVELW][LEVELH] = {};
	DepthMatrix[LEVELW][LEVELH] = {};

	for (int x = 0; x <= LEVELW; x++) {
		for (int y = 0; y <= LEVELH; y++) {
			LevelMatrix[x][y] = 3;// rand() % 2 + 1;
		}
	}

	int count = 0;//temp
	
	int HYP = 0;
	int RAD = 5;//area that tiles extend from 
	for (int x = RAD; x <= LEVELW - RAD; x++) {
		for (int y = RAD; y <= LEVELH - RAD; y++) {

			if(rand()%20 == 1){//small chance of creating tile circle

				LevelMatrix[x][y] = 0;//sets center as full tile

				for (int a = -RAD; a <= RAD; a++) {//running through all coordinates within radius
					for (int b = -RAD; b <= RAD; b++) {			

						if ((sqrt((a*a) + (b*b))) < RAD) {//checking tiles with TILEAREA diameter circle.
							if (!(a == 0 && b == 0)) {//a and b cannot both equal 0 for some reason.
								HYP = abs(sqrt((a*a) + (b*b)));//finding hypotenuse created by a and b
								LevelMatrix[x + a][y + b] = rand()%HYP+1;
							}
						}

					}
				}

			}
						
		}
	}
	
	for (int x = 1; x <= LEVELW - 1; x++) {
		for (int y = 1; y <= LEVELH - 1; y++) {
				Tile *tile = new Tile();
				tile->Init(TerrainImage, x*TILEW, y*TILEH, 0, 200*LevelMatrix[x][y], 200*(rand()%2), 200, 200);//position and dimensions/position of image
				AllObjects.push_back(tile);
				TileList.push_back(tile);
		}
	}

	for (int x = 1; x <= LEVELW - 1; x++) {
		for (int y = 1; y <= LEVELH - 1; y++) {
			if (LevelMatrix[x][y] == 0) 
			{
				Banner *banner = new Banner();
				banner->Init(TerrainImage, x*TILEH, (y*TILEW) - 200, 0, 1000, 0, 200, 600);
				AllObjects.push_back(banner);
				ObjectCollisionList.push_back(banner);
			}
		}
	}
	cout << ID << endl;
		for (int a = 1; a <= 400; a++) {
			int x = rand() % (LEVELW*TILEW - TILEW*2) + TILEW;
			int y = rand() % (LEVELH*TILEH - TILEH*2) + TILEH;
			Grass *grass = new Grass();
				grass->Init(x, y, 10, 1, 5, 1);
				GrassList.push_back(grass);
		}
		//grass->Init(1, 1, 10, 1, 5, 1);
		//GrassList.push_back(grass);
	/*for (int x = 0; x <= LEVELW; x++) {
		for (int y = 0; y <= LEVELH; y++) {
			LevelMatrix[x][LEVELH] = 0;
			LevelMatrix[x][0] = 0;
			LevelMatrix[LEVELW][y] = 0;
			LevelMatrix[0][y] = 0;
		}
	}*/
}

//===========================================================================================================================================================================================================================
//OBJECT LIST MANAGEMENT
//===========================================================================================================================================================================================================================

void Room::ObjectUpdate()
{
	if (!paused) {

		/*counter2++;
		if (counter2 == 20)
		{
			counter2 = 0;
			counter++;
		}
		for (titer = TileList.begin(); titer != TileList.end(); ++titer)//creates wave effect
		{
			if ((*titer)->GetX() == counter*TILEW && (*titer)->GetY() < counter * TILEH) {
				(*titer)->RiseTo(2);
			}
		}
		if (counter >= LEVELW)
			counter = 0;
		*/
		for (titer = TileList.begin(); titer != TileList.end(); ++titer)//tracks depth of all tiles
		{
			int tempx = (*titer)->GetX() / TILEW;
			int tempy = (*titer)->GetY() / TILEH;
			if ((*titer)->GetZ() != DepthMatrix[tempx][tempy]) {
				DepthMatrix[tempx][tempy] = (*titer)->GetZ();
			}
		}

		for (citer = ObjectCollisionList.begin(); citer != ObjectCollisionList.end(); ++citer)//sets collidable objects depth to that of tiles underneath them.
		{
			int tempx = (*citer)->GetColX() / TILEW;
			int tempy = ((*citer)->GetColY() + (*citer)->GetColBoundX()) / TILEH;
			(*citer)->SetZ(DepthMatrix[tempx][tempy]);
		}

		/*for (citer = ObjectCollisionList.begin(); citer != ObjectCollisionList.end(); ++citer)//stops collidable objects from passing over tiles of different depth.
		{
			int tempxv = ((*citer)->GetX() + (*citer)->GetVelX()*(*citer)->GetDirX()) / TILEW;
			int tempyv = ((*citer)->GetY() + (*citer)->GetVelY()*(*citer)->GetDirY()) / TILEH;
			int tempx = (*citer)->GetX() / TILEW;
			int tempy = (*citer)->GetY() / TILEH;

			if (abs(DepthMatrix[tempxv][tempy]) - abs((*citer)->GetZ()) > 10)
				(*citer)->SetDirX(0);

			if (abs(DepthMatrix[tempx][tempyv]) - abs((*citer)->GetZ()) > 10)
				(*citer)->SetDirY(0);
		}*/

		/*for (citer = ObjectCollisionList.begin(); citer != ObjectCollisionList.end(); ++citer)//experimental means of making tiles rise in all colliding object positions.
		{
			for (titer = TileList.begin(); titer != TileList.end(); ++titer)
			{
				if ((((*titer)->GetX() + (*titer)->GetBoundX() / 2) - ((*citer)->GetX() + (*citer)->GetBoundX() / 2) < 50) &&
					(((*citer)->GetX() + (*citer)->GetBoundX() / 2) - ((*titer)->GetX() + (*titer)->GetBoundX() / 2) < 50) &&
					(((*titer)->GetY() + (*titer)->GetBoundY() / 2) - ((*citer)->GetY() + (*citer)->GetBoundY() / 2) < 50) &&
					(((*citer)->GetY() + (*citer)->GetBoundY() / 2) - ((*titer)->GetY() + (*titer)->GetBoundY() / 2) < 50)) {

					(*titer)->RiseTo(2);//rising
				}
			}
		}*/

		for (iter = AllObjects.begin(); iter != AllObjects.end(); ++iter)
		{
			(*iter)->Update();
		}
	}
}

void Room::ObjectRender(double cameraXPos, double cameraYPos)
{
	sort(AllObjects.begin(), AllObjects.end(), compare);

	for (iter = AllObjects.begin(); iter != AllObjects.end(); ++iter)
	{
		(*iter)->Render(cameraXPos, cameraYPos);
	}

	for (giter = GrassList.begin(); giter != GrassList.end(); ++giter)
	{
		(*giter)->Update(cameraXPos, cameraYPos);
	}
}

void Room::ObjectCollision()
{
	for (citer = ObjectCollisionList.begin(); citer != ObjectCollisionList.end(); ++citer)
	{
		for (citer2 = citer; citer2 != ObjectCollisionList.end(); ++citer2)
		{
			if ((*citer)->CollisionCheck((*citer2)))
			{
				(*citer)->Collided((*citer2));
				(*citer2)->Collided((*citer));
			}
		}
	}
}

void Room::ObjectDeletion()
{
	for (iter = AllObjects.begin(); iter != AllObjects.end();)
	{
		if (!(*iter)->GetValid())
		{
			delete (*iter);
			iter = AllObjects.erase(iter);
		}
		else
			iter++;
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

//===========================================================================================================================================================================================================================
//SHUFFLING
//===========================================================================================================================================================================================================================

void Room::Shuffle(int shuffletype)
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

void Room::RedClockwise()
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
void Room::RedCounterClockwise()
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

void Room::WhiteClockwise()
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
void Room::WhiteCounterClockwise()
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

void Room::BlueClockwise()
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
void Room::BlueCounterClockwise()
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

void Room::YellowClockwise()
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
void Room::YellowCounterClockwise()
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

void Room::GreenClockwise()
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
void Room::GreenCounterClockwise()
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

void Room::OrangeClockwise()
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
void Room::OrangeCounterClockwise()
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

