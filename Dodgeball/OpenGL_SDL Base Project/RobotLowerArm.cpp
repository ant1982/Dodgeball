#include "RobotLowerArm.h"

RobotLowerArm::RobotLowerArm(Vector3D startLocation, string modelFileName, char* path) :RobotUpperArm(startLocation, modelFileName, path) {

	mPosition = startLocation;
	std::strcpy(fileName, modelFileName.c_str());
	mLowerArmObject = new Object3DS(Vector3D(startLocation), modelFileName);	
	lowerArmRotation = 0.0f;
}

RobotLowerArm::~RobotLowerArm() {

}

void RobotLowerArm::Render() {

	glTranslatef(12, 0, 37);
	glRotatef(lowerArmRotation, 0, 1, 0);
	glTranslatef(-12, 0, -37);
	RobotBaseClass::Render();
}

void RobotLowerArm::Update(float deltaTime, SDL_Event e) {

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_3:
			lowerArmRotation -= 2.0f;
			break;

		case SDLK_4:
			lowerArmRotation += 2.0f;
			break;

		default:
			break;
		}
	}
	if (lowerArmRotation >= 45.0f) {

		lowerArmRotation = 45.0f;
	}
	if (lowerArmRotation <= -45.0f)
	{
		lowerArmRotation = -45.0f;
	}
	if (true)
	{

	}
}