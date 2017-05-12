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

	bool collision;//the collision of two objects.	
	bool animating;

protected:
	int verticality;//basic grouping that object is in (TILE, UNIT, DECOR, etc.)
	bool valid;//determines whether object should be deleted or not.

	double x;
	double y;
	double z;//z coordinate adds/subtracts from y coordinate. used for synthetic depth (game isn't actually 3D!)

	double velX;
	double velY;
	double velZ;

	double dirX;
	double dirY;
	double dirZ;

	double angle;//angle of rotation of object.
	ALLEGRO_COLOR transparency;//transparency of rendered image.

	double boundX;//width and height of object within game.
	double boundY;

	int imageX;//position of image region being used.
	int imageY;
	double imageboundX;//width and height of image region being used.
	double imageboundY;

	int colX;//position and size of object that is collidable.
	int colY;
	int colboundX;
	int colboundY;

	int maxFrame;//number of frames to row currently being used.
	int curFrame;//current frame the class is on.

	int maxRow;//number of rows within image (should not change).
	int curRow;//current row class is on.

	bool FlipHorizontal;//tracks whether or not to flip image. Default faces left.

	ALLEGRO_BITMAP *image;

public:

	Object();
	void virtual Destroy();
	void Init(double x, double y, double z, double boundX, double boundY, int imageX, int imageY, double imageboundX, double imageboundY, int colX, int colY, int colboundX, int colboundY);

	//==============================================
	//CLASS MANAGEMENT
	//==============================================
	void virtual Update();
	void virtual Render(double cameraXPos, double cameraYPos);

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

	double GetColX() { return colX; }
	double GetColY() { return colY; }

	void SetColX(double colx) { Object::colX = colX; }
	void SetColY(double coly) { Object::colY = colY; }

	//==============================================
	//SIZE ACCESS
	//==============================================
	double GetBoundX() { return boundX; }
	double GetBoundY() { return boundY; }

	void SetBoundX(double boundX) { Object::boundX = boundX; }
	void SetBoundY(double boundY) { Object::boundY = boundY; }

	int GetColBoundX() { return colboundX; }
	int GetColBoundY() { return colboundY; }

	void SetColBoundX(int colboundX) { Object::colboundX = colboundX; }
	void SetColBoundY(int colboundY) { Object::colboundY = colboundY; }
	//==============================================
	//DELETION ACCESS/MODIFICATION
	//==============================================
	bool GetValid() { return valid; }
	void SetValid(bool valid) { Object::valid = valid; }

	//==============================================
	//COLLISION
	//==============================================
	//bool GetCollidable() { return collidable; }
	//void SetCollidable(bool collidable) { Object::collidable = collidable; }

	bool CollisionCheck(Object *otherObject);
	void virtual Collided(Object *otherObject);

	//==============================================
	//OTHER
	//==============================================
	bool GetAnimating() { return animating; }
	void SetAnimating(bool animating) { Object::animating = animating; }

	int GetVerticality() { return verticality; }
	void SetVerticality(int verticality) { Object::verticality = verticality; }
};