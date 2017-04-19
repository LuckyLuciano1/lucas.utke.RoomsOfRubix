#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include <vector>
using namespace std;

class Object
{
private:

	bool collidable;//ability for object to collide.
	bool collision;//the collision of two objects.
	bool valid;//determines whether object should be deleted or not.

protected:

	double x;
	double y;
	double z;//z coordinate adds/subtracts from y coordinate. used for synthetic depth (game isn't actually 3D!)

	double velX;
	double velY;
	double velZ;

	double dirX;
	double dirY;
	double dirZ;

	double angle;//angle of rotation of object

	int boundX;//width and height of object within game.
	int boundY;

	int imageX;//position of image region being used.
	int imageY;
	int imageboundX;//width and height of image region being used.
	int imageboundY;

	int maxFrame;//number of frames to row currently being used.
	int curFrame;//current frame the class is on.

	int maxRow;//number of rows within image (should not change).
	int curRow;//current row class is on.

	ALLEGRO_BITMAP *image;

public:

	Object();
	void virtual Destroy();
	void Init(double x, double y, double z);

	//==============================================
	//CLASS MANAGEMENT
	//==============================================
	void virtual Update(double cameraX, double cameraY);
	void virtual Render();

	//==============================================
	//COORDINATE ACCESS/MODIFICATION
	//==============================================
	double GetX() { return x; }
	double GetY() { return y; }
	double GetZ() { return z; }

	void SetX(double x) { Object::x = x; }
	void SetY(double y) { Object::y = y; }
	void SetZ(double z) { Object::z = z; }

	double GetDirX() { return dirX; }
	double GetDirY() { return dirY; }
	double GetDirZ() { return dirZ; }

	void SetDirX(double dirX) { Object::dirX = dirX; }
	void SetDirY(double dirY) { Object::dirY = dirY; }
	void SetDirZ(double dirZ) { Object::dirZ = dirZ; }

	double GetVelX() { return velX; }
	double GetVelY() { return velY; }
	double GetVelZ() { return velZ; }

	void SetVelX(double velX) { Object::velX = velX; }
	void SetVelY(double velY) { Object::velY = velY; }
	void SetVelZ(double velZ) { Object::velZ = velZ; }

	//==============================================
	//SIZE ACCESS
	//==============================================
	int GetBoundX() { return boundX; }
	int GetBoundY() { return boundY; }

	//==============================================
	//DELETION ACCESS/MODIFICATION
	//==============================================
	bool GetValid() { return valid; }
	void SetValid(bool valid) { Object::valid = valid; }

	//==============================================
	//COLLISION
	//==============================================
	bool GetCollidable() { return collidable; }
	void SetCollidable(bool collidable) { Object::collidable = collidable; }

	bool CollisionCheck(Object *otherObject);
	void virtual Collided(Object *otherObject);
};