#include "Denzil.h"
#include "Collision.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "../gl/glut.h"
#include "Dodgeball.h"

using namespace std;


Denzil::Denzil(string modelFileName) : GameObject(){

	

	std::strcpy(fileName, modelFileName.c_str());

	meshAsset = new Object3DS(Vector3D(position), modelFileName);
	boundingBox = new Box(position, 20, 20, 20);

	position.x = -88.0f;
	position.y = 20.0f;
	position.z = 160.0f;

	velocity.x = 100.0f;
	velocity.z = 100.0f;

	mAcceleration.x = 0.1f;
	mAcceleration.y = 0.0f;
	mAcceleration.z = 0.1f;

	Hits = 0;
	Zoffset = 5.0f;
	bool reachedExit = false;
}

Denzil::~Denzil() {

	delete meshAsset;
	meshAsset = NULL;
}

void Denzil::Update(float deltaTime, SDL_Event e) {

	boundingBox->SetCollided(false);
	/*CollisionCentre = position;*/

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			position.z -= velocity.z*deltaTime + mAcceleration.z * (0.5 *deltaTime * deltaTime);
			velocity.z -= mAcceleration.z *deltaTime;
			break;
		case SDLK_s:
			position.z += velocity.z*deltaTime + mAcceleration.z * (0.5 *deltaTime * deltaTime);
			velocity.z += mAcceleration.z *deltaTime;
			/*position.z += 0.5f;*/
			break;
		case SDLK_a:
			position.x -= velocity.x*deltaTime + mAcceleration.x * (0.5 *deltaTime * deltaTime);
			velocity.x -= mAcceleration.x *deltaTime;
			break;
		case SDLK_d:
			position.x += velocity.x*deltaTime + mAcceleration.x * (0.5 *deltaTime * deltaTime);
			velocity.x += mAcceleration.x *deltaTime;
			break;

		case SDLK_p:
			cout << "X position is: " << position.x << endl;
			cout << "Y position is: " << position.y << endl;
			cout << "Z position is: " << position.z << endl;
		default:
			break;
		}
	}

	boundingBox->Update(position);
}

void Denzil::Render() {

	if (boundingBox->GetCollided()) {
		
		/*cout << "denzil hit" << endl;*/
	}

	if (position.z <= -154)
	{
		SetExitReached();
	}

	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);
	/*glRotatef(40, rotation.x, rotation.y, rotation.z);	*/
	glutWireCube(25);
	meshAsset->Render();
	glPopMatrix();

	
	for (int i = 0; i < Hits; i++) {
				
		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);

		/*spawnedBall.push_back(new Dodgeball("Dodgeball.3ds"));*/
		for (int j = 0; j < Hits; j++) {
			glPushMatrix();
			glTranslatef(0, 0, Zoffset);
			glutSolidSphere(5, 10, 10);
		}
		
		glPopMatrix();
		glPopMatrix();
		
	}
}

void Denzil::loadTGAFile(char* path) {

	meshAsset->loadTGAFile(path);
}

void Denzil::AddFollowingBalls(int numberOfHits) {

	/*vector<Dodgeball *> spawnedBall;*/
	Hits = numberOfHits;
	Zoffset += 5.0f;
}

void Denzil::SetExitReached() {

	reachedExit = true;
}

bool Denzil::ReachedExit() {

	if (reachedExit == true)
	{
		return true;
	}
	return false;
}

Box * Denzil::GetBoundingBox() {
	return boundingBox;
}