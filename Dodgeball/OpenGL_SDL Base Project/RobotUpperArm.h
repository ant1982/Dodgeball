#pragma once

#ifndef _ROBOTUPPERARM_H
#define _ROBOTUPPERARM_H

#include "RobotBaseClass.h"

class RobotUpperArm : public RobotBaseClass {


public:

	RobotUpperArm(Vector3D startLocation, string modelFileName,char* path);
	~RobotUpperArm();

	void Render();
	void Update(float deltaTime, SDL_Event e);

protected:

private:

	Vector3D mPosition;
	Object3DS* mUpperArmObject;
	float upperArmRotation;

};

#endif // _ROBOTUPPERARM_H

