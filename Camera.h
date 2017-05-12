#pragma once

#include <iostream>
#include "Globals.h"
#include "Object.h"
#include <vector>

using namespace std;

class Camera
{
protected:
	double cameraXDir;
	double cameraYDir;

	double cameraXPos;
	double cameraYPos;

	bool paused;
public:
	Camera();
	void virtual Destroy();
	void Init(double cameraXPos, double cameraYPos);

	void Follow(Object *object);
	void MoveTo(double x, double y);

	double GetCameraXPos() { return cameraXPos; }
	double GetCameraYPos() { return cameraYPos; }
	double GetCameraXDir() { return cameraXDir; }
	double GetCameraYDir() { return cameraYDir; }

	void SetCameraXPos(double cameraXPos) { Camera::cameraXPos = cameraXPos; }
	void SetCameraYPos(double cameraYPos) { Camera::cameraYPos = cameraYPos; }
	void SetCameraXDir(double cameraXDir) { Camera::cameraXDir = cameraXDir; }
	void SetCameraYDir(double cameraYDir) { Camera::cameraYDir = cameraYDir; }

	void Pause() { paused = true; }
	void Resume() { paused = false; }
};
