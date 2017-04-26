#include "Globals.h"
#include "Room.h"
#include "Player.h"
#include "Tile.h"
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;

bool compare(Object *L1, Object *L2);//function for sorting values. not part of the room class, merely inhabits same file

Room::Room(){}

void Room::Destroy() {}

void Room::Init(char ID, int x, int y, int z, Player *player, ALLEGRO_BITMAP *TerrainImage)
{
	Room::ID = ID;
	Room::x = x;
	Room::y = y;
	Room::z = z;

	ObjectList.push_back(player);
	ObjectCollisionList.push_back(player);

	LevelMatrix[LEVELW][LEVELH] = {};

	for (int x = 0; x < LEVELW; x++) {
		for (int y = 0; y < LEVELH; y++) {
			LevelMatrix[x][y] = 1;// rand() % 2 + 1;
		}
	}
	for (int x = 0; x < LEVELW; x++) {
		for (int y = 0; y < LEVELH; y++) {
			if (LevelMatrix[x][y] == 1) {
				Tile *tile = new Tile();
				tile->Init(TerrainImage, x*TILEW, y*TILEH, TILEW*x*rand() % 5, 0, 0, 200, 200);//position and dimensions/position of image
				ObjectList.push_back(tile);
			}
		}
	}
}

//===========================================================================================================================================================================================================================
//OBJECT LIST MANAGEMENT
//===========================================================================================================================================================================================================================

void Room::ObjectUpdate(int CameraXDir, int CameraYDir) 
{
	for (iter = ObjectList.begin(); iter != ObjectList.end(); ++iter)
	{
		(*iter)->Update(CameraXDir, CameraYDir);
	}
}

void Room::ObjectRender()
{
	sort(ObjectList.begin(), ObjectList.end(), compare);
	for (iter = ObjectList.begin(); iter != ObjectList.end(); ++iter)
	{
		(*iter)->Render();
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
	for (iter = ObjectList.begin(); iter != ObjectList.end();)
	{
		if (!(*iter)->GetValid())
		{
			delete (*iter);
			iter = ObjectList.erase(iter);
		}
		else
			iter++;
	}
}

bool compare(Object *L1, Object *L2) {

	//primary condition
	if ((*L1).GetZ() < (*L2).GetZ()) return true;
	if ((*L2).GetZ() < (*L1).GetZ()) return false;

	//secondary condition
	if ((*L1).GetY() + (*L1).GetBoundY() < (*L2).GetY() + (*L2).GetBoundY()) return true;
	if ((*L2).GetY() + (*L2).GetBoundY() < (*L1).GetY() + (*L1).GetBoundY()) return false;

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
	else if (x == 0 && y == 1 && z == 0) {//D
		x = 0;//O
		y = 2;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 0) {//G
		x = 0;//X
		y = 2;
		z = 2;
	}
	else if (x == 0 && y == 0 && z == 1) {//J
		x = 0;//D
		y = 1;
		z = 0;
	}
	else if (x == 0 && y == 1 && z == 1) {//M
		x = 0;//N/A
		y = 1;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 1) {//O
		x = 0;//U
		y = 1;
		z = 2;
	}
	else if (x == 0 && y == 0 && z == 2) {//R
		x = 0;//A
		y = 0;
		z = 0;
	}
	else if (x == 0 && y == 1 && z == 2) {//U
		x = 0;//J
		y = 0;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 2) {//X
		x = 0;//R
		y = 0;
		z = 2;
	}
	else
		cout << "ERROR - WHITECLOCKWISE" << endl;
}
void Room::WhiteCounterClockwise()
{
	if (x == 0 && y == 0 && z == 0) {//A
		x = 0;//R
		y = 0;
		z = 2;
	}
	else if (x == 0 && y == 1 && z == 0) {//D
		x = 0;//J
		y = 0;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 0) {//G
		x = 0;//A
		y = 0;
		z = 0;
	}
	else if (x == 0 && y == 0 && z == 1) {//J
		x = 0;//U
		y = 1;
		z = 2;
	}
	else if (x == 0 && y == 1 && z == 1) {//M
		x = 0;//N/A
		y = 1;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 1) {//O
		x = 0;//D
		y = 1;
		z = 0;
	}
	else if (x == 0 && y == 0 && z == 2) {//R
		x = 0;//X
		y = 2;
		z = 2;
	}
	else if (x == 0 && y == 1 && z == 2) {//U
		x = 0;//O
		y = 2;
		z = 1;
	}
	else if (x == 0 && y == 2 && z == 2) {//X
		x = 0;//G
		y = 2;
		z = 0;
	}
	else
		cout << "ERROR - " << endl;
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
		y = 0;
		z = 1;
	}
	else if (x == 0 && y == 0 && z == 0) {//A
		x = 0;//R
		y = 0;
		z = 2;
	}
	else if (x == 2 && y == 0 && z == 1) {//L
		x = 1;//B
		y = 0;
		z = 0;
	}
	else if (x == 1 && y == 0 && z == 1) {//K
		x = 1;//N/A
		y = 0;
		z = 1;
	}
	else if (x == 0 && y == 0 && z == 1) {//J
		x = 1;//S
		y = 0;
		z = 2;
	}
	else if (x == 2 && y == 0 && z == 2) {//T
		x = 2;//C
		y = 0;
		z = 0;
	}
	else if (x == 1 && y == 0 && z == 2) {//S
		x = 2;//L
		y = 0;
		z = 1;
	}
	else if (x == 0 && y == 0 && z == 2) {//R
		x = 2;//T
		y = 0;
		z = 2;
	}
	else
		cout << "ERROR - BLUECLOCKWISE" << endl;
}
void Room::BlueCounterClockwise()
{
	if (x == 2 && y == 0 && z == 0) {//C
		x = 2;//T
		y = 0;
		z = 2;
	}
	else if (x == 1 && y == 0 && z == 0) {//B
		x = 2;//L
		y = 0;
		z = 1;
	}
	else if (x == 0 && y == 0 && z == 0) {//A
		x = 2;//C
		y = 0;
		z = 0;
	}
	else if (x == 2 && y == 0 && z == 1) {//L
		x = 1;//S
		y = 0;
		z = 2;
	}
	else if (x == 1 && y == 0 && z == 1) {//K
		x = 1;//N/A
		y = 0;
		z = 1;
	}
	else if (x == 0 && y == 0 && z == 1) {//J
		x = 1;//B
		y = 0;
		z = 0;
	}
	else if (x == 2 && y == 0 && z == 2) {//T
		x = 0;//R
		y = 0;
		z = 2;
	}
	else if (x == 1 && y == 0 && z == 2) {//S
		x = 0;//J
		y = 0;
		z = 1;
	}
	else if (x == 0 && y == 0 && z == 2) {//R
		x = 0;//A
		y = 0;
		z = 0;
	}
	else
		cout << "ERROR - BLUECOUNTERCLOCKWISE" << endl;
}

void Room::YellowClockwise()
{
	if (x == 2 && y == 2 && z == 0) {//I
		x = 2;//C
		y = 0;
		z = 0;
	}
	else if (x == 2 && y == 1 && z == 0) {//F
		x = 2;//L
		y = 0;
		z = 1;
	}
	else if (x == 2 && y == 0 && z == 0) {//C
		x = 2;//T
		y = 0;
		z = 2;
	}
	else if (x == 2 && y == 2 && z == 1) {//Q
		x = 2;//F
		y = 1;
		z = 0;
	}
	else if (x == 2 && y == 1 && z == 1) {//N
		x = 2;//N/A
		y = 1;
		z = 1;
	}
	else if (x == 2 && y == 0 && z == 1) {//L
		x = 2;//W
		y = 1;
		z = 2;
	}
	else if (x == 2 && y == 2 && z == 2) {//Z
		x = 2;//I
		y = 2;
		z = 0;
	}
	else if (x == 2 && y == 1 && z == 2) {//W
		x = 2;//Q
		y = 2;
		z = 1;
	}
	else if (x == 2 && y == 0 && z == 2) {//T
		x = 2;//Z
		y = 2;
		z = 2;
	}
	else
		cout << "ERROR - YELLOWCLOCKWISE" << endl;
}
void Room::YellowCounterClockwise()
{
	if (x == 2 && y == 2 && z == 0) {//I
		x = 2;//Z
		y = 2;
		z = 2;
	}
	else if (x == 2 && y == 1 && z == 0) {//F
		x = 2;//Q
		y = 2;
		z = 1;
	}
	else if (x == 2 && y == 0 && z == 0) {//C
		x = 2;//I
		y = 2;
		z = 0;
	}
	else if (x == 2 && y == 2 && z == 1) {//Q
		x = 2;//W
		y = 1;
		z = 2;
	}
	else if (x == 2 && y == 1 && z == 1) {//N
		x = 2;//N/A
		y = 1;
		z = 1;
	}
	else if (x == 2 && y == 0 && z == 1) {//L
		x = 2;//F
		y = 1;
		z = 0;
	}
	else if (x == 2 && y == 2 && z == 2) {//Z
		x = 2;//T
		y = 0;
		z = 2;
	}
	else if (x == 2 && y == 1 && z == 2) {//W
		x = 2;//L
		y = 0;
		z = 1;
	}
	else if (x == 2 && y == 0 && z == 2) {//T
		x = 2;//C
		y = 0;
		z = 0;
	}
	else
		cout << "ERROR - YELLOWCOUNTERCLOCKWISE" << endl;
}

void Room::GreenClockwise()
{
	if (x == 0 && y == 2 && z == 0) {//G
		x = 0;//X
		y = 2;
		z = 2;
	}
	else if (x == 1 && y == 2 && z == 0) {//H
		x = 0;//O
		y = 2;
		z = 1;
	}
	else if (x == 2 && y == 2 && z == 0) {//I
		x = 0;//G
		y = 2;
		z = 0;
	}
	else if (x == 0 && y == 2 && z == 1) {//O
		x = 1;//Y
		y = 2;
		z = 2;
	}
	else if (x == 1 && y == 2 && z == 1) {//P
		x = 1;//N/A
		y = 2;
		z = 1;
	}
	else if (x == 2 && y == 2 && z == 1) {//Q
		x = 1;//H
		y = 2;
		z = 0;
	}
	else if (x == 0 && y == 2 && z == 2) {//X
		x = 2;//Z
		y = 2;
		z = 2;
	}
	else if (x == 1 && y == 2 && z == 2) {//Y
		x = 2;//Q
		y = 2;
		z = 1;
	}
	else if (x == 2 && y == 2 && z == 2) {//Z
		x = 2;//I
		y = 2;
		z = 0;
	}
	else
		cout << "ERROR - GREENCLOCKWISE" << endl;
}
void Room::GreenCounterClockwise()
{
	if (x == 0 && y == 2 && z == 0) {//G
		x = 2;//I
		y = 2;
		z = 0;
	}
	else if (x == 1 && y == 2 && z == 0) {//H
		x = 2;//Q
		y = 2;
		z = 1;
	}
	else if (x == 2 && y == 2 && z == 0) {//I
		x = 2;//Z
		y = 2;
		z = 2;
	}
	else if (x == 0 && y == 2 && z == 1) {//O
		x = 1;//H
		y = 2;
		z = 0;
	}
	else if (x == 1 && y == 2 && z == 1) {//P
		x = 1;//N/A
		y = 2;
		z = 1;
	}
	else if (x == 2 && y == 2 && z == 1) {//Q
		x = 1;//Y
		y = 2;
		z = 2;
	}
	else if (x == 0 && y == 2 && z == 2) {//X
		x = 0;//G
		y = 2;
		z = 0;
	}
	else if (x == 1 && y == 2 && z == 2) {//Y
		x = 0;//O
		y = 2;
		z = 1;
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
	if (x == 2 && y == 0 && z == 2) {//T
		x = 2;//Z
		y = 2;
		z = 2;
	}
	else if (x == 1 && y == 0 && z == 2) {//S
		x = 2;//W
		y = 1;
		z = 2;
	}
	else if (x == 0 && y == 0 && z == 2) {//R
		x = 2;//T
		y = 0;
		z = 2;
	}
	else if (x == 2 && y == 1 && z == 2) {//W
		x = 1;//Y
		y = 2;
		z = 2;
	}
	else if (x == 1 && y == 1 && z == 2) {//V
		x = 1;//N/A
		y = 1;
		z = 2;
	}
	else if (x == 0 && y == 1 && z == 2) {//U
		x = 1;//S
		y = 0;
		z = 2;
	}
	else if (x == 2 && y == 2 && z == 2) {//Z
		x = 0;//X
		y = 2;
		z = 2;
	}
	else if (x == 1 && y == 2 && z == 2) {//Y
		x = 0;//U
		y = 1;
		z = 2;
	}
	else if (x == 0 && y == 2 && z == 2) {//X
		x = 0;//R
		y = 0;
		z = 2;
	}
	else
		cout << "ERROR - ORANGECLOCKWISE" << endl;
}
void Room::OrangeCounterClockwise()
{
	if (x == 2 && y == 0 && z == 2) {//T
		x = 0;//R
		y = 0;
		z = 2;
	}
	else if (x == 1 && y == 0 && z == 2) {//S
		x = 0;//U
		y = 1;
		z = 2;
	}
	else if (x == 0 && y == 0 && z == 2) {//R
		x = 0;//X
		y = 2;
		z = 2;
	}
	else if (x == 2 && y == 1 && z == 2) {//W
		x = 1;//S
		y = 0;
		z = 2;
	}
	else if (x == 1 && y == 1 && z == 2) {//V
		x = 1;//N/A
		y = 1;
		z = 2;
	}
	else if (x == 0 && y == 1 && z == 2) {//U
		x = 1;//Y
		y = 2;
		z = 2;
	}
	else if (x == 2 && y == 2 && z == 2) {//Z
		x = 2;//T
		y = 0;
		z = 2;
	}
	else if (x == 1 && y == 2 && z == 2) {//Y
		x = 2;//W
		y = 1;
		z = 2;
	}
	else if (x == 0 && y == 2 && z == 2) {//X
		x = 2;//Z
		y = 2;
		z = 2;
	}
	else
		cout << "ERROR - ORANGECOUNTERCLOCKWISE" << endl;
}