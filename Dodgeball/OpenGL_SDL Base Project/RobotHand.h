#pragma once

#ifndef _ROBOTHAND_H
#define _ROBOTHAND_H

#include "RobotLowerArm.h"

class RobotHand : RobotLowerArm
{
public:

	RobotHand(Vector3D startLocation, string modelFileName, char* path);
	~RobotHand();

	void Render();

	void Update(float deltaTime, SDL_Event e);

protected:

private:
		
	Vector3D mPosition;
	Object3DS* mHandObject;
	float handRotation;

};

#endif // _ROBOTHAND_H

