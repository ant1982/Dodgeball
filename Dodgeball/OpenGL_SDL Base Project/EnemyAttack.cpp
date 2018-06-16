#include "EnemyAttack.h"
#include "Denzil.h"
#include "Collision.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "../gl/glut.h"
#include <SDL_mixer.h>

EnemyAttack::EnemyAttack(Denzil * target ,Vector3D spawnLoc) : GameObject() {
	

	position.x = spawnLoc.x;
	position.y = 30.0f;
	position.z = spawnLoc.z;

	scale = 5.0f;

	velocity.x = 0.0f;
	velocity.y = 10000 * (float)rand() / ((RAND_MAX) * 1000) - .005;
	velocity.z = 150.0f;

	rotation.x = 10 * (float)rand() / ((RAND_MAX) * 1) - .005;
	rotation.y = 10 * (float)rand() / ((RAND_MAX) * 1) - .005;
	rotation.z = 0;	

	boundingSphere = new Sphere(position, scale*1.5);

	mAcceleration.x = 0.0f;
	mAcceleration.y = -2.0f;
	mAcceleration.z = 0.0f;	

	outOfBounds = false;
	playerTarget = target;
}

EnemyAttack::~EnemyAttack() {

	delete boundingSphere;
	boundingSphere = NULL;
}

void EnemyAttack::Update(float deltaTime) {

	boundingSphere->SetCollided(false);

	position += velocity*deltaTime + mAcceleration * (0.5 *deltaTime * deltaTime);
	velocity += mAcceleration *deltaTime;

	velocity * 0.98f;

	boundingSphere->Update(position);
	if (position.z > 250.0f)
	{
		/*cout << "object out of bounds" << endl;*/
		outOfBounds = true;
	}
}

void EnemyAttack::Render() {
	
	
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(40, rotation.x, rotation.y, rotation.z);
	/*BallAsset->Render();*/
	glutSolidSphere(boundingSphere->GetBoundingRadius(), 10, 10);
	glutWireSphere(boundingSphere->GetBoundingRadius(), 10, 10);
	glPopMatrix();


}

void EnemyAttack::loadTGAFile(char* path) {

}

bool EnemyAttack::OutOfBounds() {
	if (outOfBounds == true)
	{		
		return true;
	}
	return false;
}

Sphere * EnemyAttack::GetBoundingSphere() {
	return boundingSphere;
}