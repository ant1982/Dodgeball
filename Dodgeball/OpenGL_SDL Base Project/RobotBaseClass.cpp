#include "RobotBaseClass.h"


RobotBaseClass::RobotBaseClass(Vector3D startLocation, string modelFileName) 
{
	mPosition = startLocation;
	std::strcpy(fileName, modelFileName.c_str());
	mBaseObject = new Object3DS(Vector3D(startLocation),modelFileName);
	rotation = 0.0f;
	rotationSpeed = 10.0f;
	moveBase = true;
}

RobotBaseClass::~RobotBaseClass() 
{

}

void RobotBaseClass::Update(float deltaTime, SDL_Event e) 
{
	/*rotation += rotationSpeed * deltaTime;*/
	if (moveBase == true)
	{
		RotateOn(deltaTime);
	}
	else if (moveBase == false)
	{
		RotateOff();
	}

	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		switch (e.button.button)
		{
		case SDL_BUTTON_LEFT:

			moveBase = true;
			break;
		case SDL_BUTTON_RIGHT:
			moveBase = false;
			break;
		default:
			break;
		}
	}
}

void RobotBaseClass::Render() 
{
	glRotatef(rotation, 0, 0, 1);
	mBaseObject->Render();	
}

void RobotBaseClass::loadTGAFile(char* path) {

	mBaseObject->loadTGAFile(path);

}

void RobotBaseClass::RotateOn(float deltaTime) {
		
	rotation += rotationSpeed *deltaTime;

}

void RobotBaseClass::RotateOff() {

	rotation += 0.0f;

}