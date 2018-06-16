#pragma once

#ifndef _ROBOTBASECLASS_H
#define _ROBOTBASECLASS_H

#include <Windows.H>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Commons.h"
#include <SDL.h>
#include "Texture2D.h"
#include "object3DS.h"

class RobotBaseClass {

public:

	RobotBaseClass(Vector3D startLocation, string modelFileName);
	~RobotBaseClass();

	void Update(float deltaTime, SDL_Event e);
	void Render();
	void loadTGAFile(char* path);


protected:

	char fileName[20];
	char textureName[20];

private:

	Vector3D mPosition;
	Object3DS* mBaseObject;

	float rotation;
	float rotationSpeed;
	bool moveBase;

	void RotateOn(float deltaTime);
	void RotateOff();


};

#endif // _ROBOTBASECLASS_H
