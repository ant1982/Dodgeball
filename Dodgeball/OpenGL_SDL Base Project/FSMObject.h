#pragma once

#ifndef _FSMOBJECT_H
#define _FSMOBJECT_H


#include "GameObject.h"
#include "EnemyAttack.h"
#include <cassert>
#include <vector>
#include "Commons.h"

class Denzil;
class State;

class FSMObject : public GameObject
{
	

public:
	FSMObject(string modelFileName,Denzil * player);
	~FSMObject();

	void Update(float deltaTime);	

	virtual void Render();

	void ChangeState(State* newState);

	bool PositionOneSet();
	bool Return();
	bool StartingPoint();
	bool PositionTwoSet();

	void Attack();
	void ReturnToStart();
	void MoveTowardsPlayer();
	void MoveToNewPosition();
	void Idle();
	void Timer();
	

private:

	State * pCurrentState;
	Denzil * CurrentPlayer;

	Vector3D position;
	Vector3D startPosition;
	Vector3D targetPosition;
	Vector3D newPosition;
	Object3DS* meshAsset;
	bool returnedStartLoc;
	bool positionOne;
	bool Returning;
	bool positionTwo;
	bool CanAttack;
	bool Moved;	
	float mTimer;
	int numberOfAttacks;
	vector<EnemyAttack *> attack;

};



#endif //_FSMOBJECT_H

