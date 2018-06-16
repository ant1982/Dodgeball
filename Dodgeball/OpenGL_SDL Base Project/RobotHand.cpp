#include "RobotHand.h"

RobotHand::RobotHand(Vector3D startLocation, string modelFileName, char* path) :RobotLowerArm(startLocation, modelFileName, path) {

	mPosition = startLocation;
	std::strcpy(fileName, modelFileName.c_str());
	mHandObject = new Object3DS(Vector3D(startLocation), modelFileName);	
	handRotation = 0.0f;
	
}

RobotHand::~RobotHand() {

}

void RobotHand::Render() {
	
	glTranslatef(43, 0, 30);
	glRotatef(handRotation, 0, 1, 0);
	glTranslatef(-43, 0, -30);
	RobotBaseClass::Render();	
}

void RobotHand::Update(float deltaTime, SDL_Event e) {

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_5:
			handRotation -= 2.0f;
			break;
		case SDLK_6:
			handRotation += 2.0f;
			break;
		default:
			break;
		}
	}

	if (handRotation >= 45.0f) 
	{
		handRotation = 45.0f;
	}
	if (handRotation <= -45.0f)
	{
		handRotation = -45.0f;
	}
}