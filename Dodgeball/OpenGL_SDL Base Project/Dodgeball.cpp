#include "Dodgeball.h"
#include "Collision.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "../gl/glut.h"
#include <SDL_mixer.h>

Mix_Chunk * bounce = NULL;

Dodgeball::Dodgeball(string modelFileName) : GameObject() {

	std::strcpy(fileName, modelFileName.c_str());

	BallAsset = new Object3DS(Vector3D(position), modelFileName);

	position.x = 130.0f * (float)rand() / (RAND_MAX)-65.0f;
	position.y = 80.0f * (float)rand() / (RAND_MAX)+20.0f;
	position.z = 160.0f * (float)rand() / (RAND_MAX)-75.0f;

	scale = 5.0f;
	
	velocity.x = 20.0f * (float)rand() / (RAND_MAX)-20.0f;
	velocity.y = 2000 *(float)rand() / ((RAND_MAX) * 1000) - .005;
	velocity.z = 100 *(float)rand() / ((RAND_MAX) * 1000) - .005;
	
	rotation.x = 10 * (float)rand() / ((RAND_MAX) * 1) - .005;
	rotation.y = 10 * (float)rand() / ((RAND_MAX) * 1) - .005;
	rotation.z = 0;

	Vector3D collision = position;
	Collided = false;

	boundingSphere = new Sphere(position, scale*1.6);

	mAcceleration.x = 0.5f;
	mAcceleration.y = -2.0f;
	mAcceleration.z = 0.5f;

	restitution = -1.0f;

	bounce = Mix_LoadWAV("Bounce.wav");
	if (bounce == NULL)
	{
		cout << "Failed to load scratch sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
	}

	
}

Dodgeball::~Dodgeball() {

	delete BallAsset;
	BallAsset = NULL;
}

void Dodgeball::Update(float deltaTime) {

	boundingSphere->SetCollided(false);

	if (Collided == true)
	{
		position += velocity*deltaTime + mAcceleration * (0.5 *deltaTime * deltaTime);
		velocity += mAcceleration *deltaTime;
	}

	else
	{
		position += velocity*deltaTime + mAcceleration * (0.5 *deltaTime * deltaTime);
		velocity += mAcceleration *deltaTime;
		Collided = false;
		
	}


	velocity * 0.98f;

	if (position.x > 130 || position.x < -65)		
		velocity.x *= -1;

	if (position.y > 100 || position.y < 5)
		velocity.y *= -1;

	if (position.z > 160 || position.z < -75)

		velocity.z *= -1;

	boundingSphere->Update(position);

	/*previous = position;*/
}

void Dodgeball::Render() {

	if (boundingSphere->GetCollided())
	{
		Collided = true;		
		velocity.x *= restitution;
		velocity.y *= restitution;
		velocity.z *= restitution;
		Mix_PlayChannel(-1, bounce, 0);

	}
	else if (Collided == true && boundingSphere->GetCollided())
	{
		velocity * 0.98f;
	}


	if (position.y < 5)
	{
		Mix_PlayChannel(-1, bounce, 0);
	}

	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);	
	glRotatef(40, rotation.x, rotation.y, rotation.z);	
	//glutSolidSphere(boundingSphere->GetBoundingRadius(), 10, 10);
	glutWireSphere(boundingSphere->GetBoundingRadius(), 10, 10);
	BallAsset->Render();
	glPopMatrix();

	
}

void Dodgeball::loadTGAFile(char* path) {

	BallAsset->loadTGAFile(path);
}

void Dodgeball::Respawn() {

	//reset ball position

	position.x = 120.0f * (float)rand() / (RAND_MAX)-60.0f;
	position.y = 80.0f * (float)rand() / (RAND_MAX)+20.0f;
	position.z = 300.0f * (float)rand() / (RAND_MAX)-150.0f;

	scale = 5.0f;

	velocity.x = 10; // 0 * (float)rand() / ((RAND_MAX) * 1000) - .005;
	velocity.y = 200 * (float)rand() / ((RAND_MAX) * 1000) - .005;
	velocity.z = 100 * (float)rand() / ((RAND_MAX) * 1000) - .005;

	rotation.x = 10 * (float)rand() / ((RAND_MAX) * 1) - .005;
	rotation.y = 10 * (float)rand() / ((RAND_MAX) * 1) - .005;
	rotation.z = 0;

}

Sphere * Dodgeball::GetBoundingSphere() {
	return boundingSphere;
}