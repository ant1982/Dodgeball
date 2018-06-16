#include "RobotUpperArm.h"

RobotUpperArm::RobotUpperArm(Vector3D startLocation, string modelFileName, char* path) : RobotBaseClass(startLocation, modelFileName) {

	mPosition = startLocation;
	std::strcpy(fileName, modelFileName.c_str());
	mUpperArmObject = new Object3DS(Vector3D(startLocation), modelFileName);
	RobotBaseClass::loadTGAFile(path);
	upperArmRotation = 0.0f;
}

RobotUpperArm::~RobotUpperArm() {

}

void RobotUpperArm::Render() {

	glTranslatef(0, 0, 7);
	glRotatef(upperArmRotation, 0, 1, 0);
	glTranslatef(0, 0, -7);	
	RobotBaseClass::Render();
}



void RobotUpperArm::Update(float deltaTime, SDL_Event e) {
	
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_1:
			upperArmRotation -= 2.0f;
			break;

		case SDLK_2:
			upperArmRotation += 2.0f;
			break;

		default:
			break;
		}
	}
	if (upperArmRotation >= 22.5f) {

		upperArmRotation = 22.5f;
	}
	if (upperArmRotation <= -22.5f)
	{
		upperArmRotation = -22.5f;
	}
}