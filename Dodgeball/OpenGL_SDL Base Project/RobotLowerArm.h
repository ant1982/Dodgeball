#pragma once

#include "RobotUpperArm.h"

#ifndef _ROBOTLOWERARM_H
#define _ROBOTLOWERARM_H

class RobotLowerArm: public RobotUpperArm
{
public:
	RobotLowerArm(Vector3D startLocation, string modelFileName, char* path);
	~RobotLowerArm();

	void Render();

	void Update(float deltaTime, SDL_Event e);

private:

	Vector3D mPosition;
	Object3DS* mLowerArmObject;
	float lowerArmRotation;

};

#endif // _ROBOTLOWERARM_H

