#include "WinZone.h"
#include "Collision.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "../gl/glut.h"

WinZone::WinZone(Vector3D finishPosition) :GameObject() {

	mPosition = finishPosition;

	radius = 20.0f;

	boundingSphere = new Sphere(mPosition, radius*1.5);

}

WinZone::~WinZone() {

	//delete boundingSphere;
	//boundingSphere = NULL;
}

void WinZone::Update(float deltaTime, SDL_Event e) {

	boundingSphere->SetCollided(false);
}

void WinZone::Render() {

	
	glPushMatrix();
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	glutWireSphere(boundingSphere->GetBoundingRadius(), 10, 10);
	glPopMatrix();
}

//Sphere * WinZone::GetBoundingSphere() {	
//		return boundingSphere;	
//}