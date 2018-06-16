#include "FSMObject.h"
#include "Denzil.h"
#include "State.h"
#include "EnemyStates.h"
#include "Collision.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "../gl/glut.h"
#include <stdio.h>
#include <iostream>

using namespace::std;

clock_t startTime = NULL;
float mTimer = 0.0f;

FSMObject::FSMObject(string modelFileName, Denzil * currentPlayer) : GameObject(), pCurrentState(EnemyIdle::Instance()) {

	float mTimer = 0.0f;
	startTime = clock();
		
	srand(time(NULL));
	std::strcpy(fileName, modelFileName.c_str());

	position.x =0.0f;
	position.y =20.0f;
	position.z = 0.0f;

	startPosition.x = 0.0f;
	startPosition.y = 20.0f;
	startPosition.z = 0.0f;

	targetPosition.x = -45.0f;
	targetPosition.y = 20.0f;
	targetPosition.z = -15.0f;

	newPosition.x = 45.0f;
	newPosition.y = 20.0f;
	newPosition.z = -15.0f;

	meshAsset = new Object3DS(Vector3D(position), modelFileName);
	CurrentPlayer = currentPlayer;
	numberOfAttacks = 0;

	positionOne = false;
	Returning = false;
	returnedStartLoc = true;
	positionTwo = false;
	CanAttack = true;
}

FSMObject::~FSMObject() {

	delete pCurrentState;
	pCurrentState = NULL;
}

void FSMObject::ChangeState(State* newState) {

	assert(pCurrentState && newState);

	//call the exit method of the existing state
	pCurrentState->Exit(this);

	//change state to the new state
	pCurrentState = newState;

	//call the entry method of the new state
	pCurrentState->Enter(this);
}

void FSMObject::Update(float deltaTime) {

	if (pCurrentState)
	{
		pCurrentState->Execute(this);
	}
	
	mTimer = (clock() - startTime) / CLOCKS_PER_SEC;

	if (mTimer == 2.0f)
	{
		//cout << "clock has reached 5 seconds" << endl;
		Timer();
	}

	int temp = rand() % 3 + 1;
	/*temp = 2;*/

	if (!Moved && returnedStartLoc)
	{
		switch (temp)
		{
		case 1:
			positionOne = true;			
			Moved = true;
			returnedStartLoc = false;
			break;
		case 2:
			positionTwo = true;			
			Moved = true;
			returnedStartLoc = false;			
			break;
		case 3:		
			Moved = true;
			Attack();
			break;

		default:
			break;
		}
	}

	if (position.x >= 0.0f && position.y == 20.0f && position.z <= 0.0f || position.x <= 0.0f && position.y == 20.0f && position.z <= 0.0f)
	{		
		Moved = false;
		Returning = false;
		returnedStartLoc = true;
				
	}		

	for (int i = 0; i < attack.size(); i++) {
		attack[i]->Update(deltaTime);
	}


	for (int i = 0; i < attack.size(); i++) {
		if (Collision::BoxCircleCollision(CurrentPlayer->GetBoundingBox(), attack[i]->GetBoundingSphere())){
						
			numberOfAttacks++;
			CurrentPlayer->AddFollowingBalls(numberOfAttacks);
			attack.clear();
			CanAttack = true;
		}
	}

	for (int i = 0; i < attack.size(); i++)
	{
		attack[i]->OutOfBounds();		
		if (attack[i]->OutOfBounds()) {
			attack.clear();
			CanAttack = true;
		}
	}	
}

void FSMObject::Render() {

	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);
	/*glRotatef(40, rotation.x, rotation.y, rotation.z);	*/
	glutWireCube(25);
	meshAsset->Render();
	glPopMatrix();

	if (!attack.empty())
	{
		for (int i = 0; i < attack.size(); i++) {
			attack[i]->Render();
		}
	}

}

bool FSMObject::PositionOneSet() {

	if (positionOne)
	{
		return true;
	}

	return false;
}

bool FSMObject::Return() {

	if (Returning)
	{
		return true;
	}

	return false;
}

bool FSMObject::StartingPoint() {

	if (returnedStartLoc)
	{
		return true;
	}

	return false;
}

bool FSMObject::PositionTwoSet() {

	if (positionTwo)
	{
		return true;
	}

	return false;
}

void FSMObject::Idle() {

}

void FSMObject::ReturnToStart() {

	//testing return to start position
	
	float x = startPosition.x - position.x;
	float y = startPosition.y - position.y;
	float z = startPosition.z - position.z;

	float dSquared = sqrt((x * x) + (y * y) + (z *z));

	if (dSquared < 100)
	{
		position.x += 0.1 * 10 * (x/ dSquared);
		position.y += 0.1 * 10 * (y/ dSquared);
		position.z += 0.1 * 10 * (z/ dSquared);
	}	
}

void FSMObject::MoveTowardsPlayer() {

	//testing movement via state machine

	float x = position.x - targetPosition.x;
	float y = position.y - targetPosition.y;
	float z = position.z - targetPosition.z;

	float dSquared = sqrt((x * x) + (y * y) + (z *z));

	if (dSquared < 100)
	{
		position.x += 0.1 * 10 * (x / dSquared);
		position.y += 0.1 * 10 * (y / dSquared);
		position.z += 0.1 * 10 * (z / dSquared);
	}
}

void FSMObject::MoveToNewPosition() {

	float x = position.x - newPosition.x;
	float y = position.y - newPosition.y;
	float z = position.z - newPosition.z;

	float dSquared = sqrt((x * x) + (y * y) + (z *z));

	if (dSquared < 100)
	{
		position.x += 0.1 * 10 * (x / dSquared);
		position.y += 0.1 * 10 * (y / dSquared);
		position.z += 0.1 * 10 * (z / dSquared);
	}

}

void FSMObject::Attack() {
	if (CanAttack == true)
	{
		attack.push_back(new EnemyAttack(CurrentPlayer, Vector3D(position.x, position.y, position.z)));
		CanAttack = false;
	}	
}

void FSMObject::Timer() {
		
	startTime = NULL;	
	mTimer = 0.0f;
	startTime = clock();
	Returning = true;
	Moved = false;
	positionOne = false;
	positionTwo = false;	
}