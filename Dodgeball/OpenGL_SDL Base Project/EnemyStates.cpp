#include "EnemyStates.h"
#include "State.h"
#include "GameObject.h"
#include "FSMObject.h"
#include <iostream>

using namespace std;

EnemyReturning * EnemyReturning::Instance() {

	static EnemyReturning instance;

	return &instance;

}

void EnemyReturning::Enter(FSMObject * gameObject) {
		
}

void EnemyReturning::Execute(FSMObject * gameObject) {

	gameObject->ReturnToStart();

	if (gameObject->StartingPoint())
	{
		gameObject->ChangeState(EnemyIdle::Instance());
	}
}

void EnemyReturning::Exit(FSMObject * gameObject) {

	
}

MoveToPositionOne * MoveToPositionOne::Instance() {

	static MoveToPositionOne instance;

	return &instance;

}

void MoveToPositionOne::Enter(FSMObject * gameObject) {

	
}

void MoveToPositionOne::Execute(FSMObject * gameObject) {
	
	gameObject->MoveTowardsPlayer();
	if (gameObject->Return())
	{
		gameObject->ChangeState(EnemyReturning::Instance());
	}
}

void MoveToPositionOne::Exit(FSMObject * gameObject) {

	gameObject->Attack();
}

EnemyIdle * EnemyIdle::Instance() {

	static EnemyIdle instance;

	return &instance;

}

void EnemyIdle::Enter(FSMObject * gameObject) {


}

void EnemyIdle::Execute(FSMObject * gameObject) {

	gameObject->Idle();
	if (gameObject->PositionOneSet())
	{
		gameObject->ChangeState(MoveToPositionOne::Instance());
	}
	if (gameObject->PositionTwoSet())
	{
		gameObject->ChangeState(MoveToPositionTwo::Instance());
	}
}

void EnemyIdle::Exit(FSMObject * gameObject) {


}

MoveToPositionTwo * MoveToPositionTwo::Instance() {

	static MoveToPositionTwo instance;

	return &instance;
}

void MoveToPositionTwo::Enter(FSMObject * gameObject) {


}

void MoveToPositionTwo::Execute(FSMObject * gameObject) {
		
	gameObject->MoveToNewPosition();

	if (gameObject->Return())
	{
		gameObject->ChangeState(EnemyReturning::Instance());
	}
}

void MoveToPositionTwo::Exit(FSMObject * gameObject) {

	gameObject->Attack();
}