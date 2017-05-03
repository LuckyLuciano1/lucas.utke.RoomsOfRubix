#include "Camera.h"
#include <math.h>
#include <iostream>

using namespace std;

Camera::Camera()
{
	cameraXDir = 0;
	cameraYDir = 0;

	cameraXPos = 0;
	cameraYPos = 0;
}

void Camera::Destroy() {}

void Camera::Init(double cameraXPos, double cameraYPos) {
	Camera::cameraXPos = cameraXPos;
	Camera::cameraYPos = cameraYPos;
}

void Camera::Follow (Object *object)
{
	/*
	if ((cameraXPos - -(object->GetVelX())*(object->GetX() - (SCREENW / 2)) / 100) > 0 && (cameraXPos + SCREENW - -(object->GetVelX())*(object->GetX() - (SCREENW / 2)) / 100) < LEVELW*TILEW)//to stop camera from exceeding mapsize
		cameraXDir = -(object->GetVelX())*(object->GetX() - (SCREENW / 2)) / 100;//velocity of camera is dependent on distance from object
	else
		cameraXDir = 0;

	if ((cameraYPos - -(object->GetVelY())*(object->GetY() - (SCREENH / 2)) / 100) > 0 && (cameraYPos + SCREENW - -(object->GetVelY())*(object->GetY() - (SCREENH / 2)) / 100) < LEVELH*TILEH)
		cameraYDir = -(object->GetVelY())*(object->GetY() - (SCREENH / 2)) / 100;
	else
		cameraYDir = 0;
	*/
	cameraXDir = ((cameraXPos + cameraXDir) + ((object->GetX() - (SCREENW / 2))+object->GetDirX()))/25;//velocity of camera is dependent on distance from object
	cameraYDir = ((cameraYPos + cameraYDir) + ((object->GetY() - (SCREENH / 2))+object->GetDirY()))/25;

	cameraXPos -= cameraXDir;
	cameraYPos -= cameraYDir;
}

void Camera::MoveTo(double x, double y)
{
	if ((cameraXPos - -(x - (SCREENW / 2)) / 100) > 0 && (cameraXPos + SCREENW - -(x - (SCREENW / 2)) / 100) < LEVELW*TILEW)//to stop camera from exceeding mapsize
		cameraXDir = -(x - (SCREENW / 2)) / 100;//velocity of camera is dependent on distance from object
	else
		cameraXDir = 0;

	if ((cameraYPos - -(y - (SCREENH / 2)) / 100) > 0 && (cameraYPos + SCREENW - -(y - (SCREENH / 2)) / 100) < LEVELH*TILEH)
		cameraYDir = -(y - (SCREENH / 2)) / 100;
	else
		cameraYDir = 0;

	cameraXPos -= cameraXDir;
	cameraYPos -= cameraYDir;
}