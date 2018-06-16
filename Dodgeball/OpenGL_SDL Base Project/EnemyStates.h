#pragma once

#ifndef _ENEMYSTATES_H
#define _ENEMYSTATES_H

#include "State.h"


class FSMObject;


class EnemyReturning : public State {

	// Enemy AI returning to start position

public:
	
	static EnemyReturning *Instance();

	virtual void Enter(FSMObject * gameObject);

	virtual void Execute(FSMObject * gameObject);

	virtual void Exit(FSMObject * gameObject);

private:

	EnemyReturning(){}

	EnemyReturning(const EnemyReturning&);
	EnemyReturning& operator=(const EnemyReturning&);	

};

class MoveToPositionOne : public State {

	// Enemy AI moves to position one

public:

	static MoveToPositionOne *Instance();

	virtual void Enter(FSMObject * gameObject);

	virtual void Execute(FSMObject * gameObject);

	virtual void Exit(FSMObject * gameObject);

private:

	MoveToPositionOne() {}

	MoveToPositionOne(const MoveToPositionOne&);
	MoveToPositionOne& operator=(const MoveToPositionOne&);

};

class EnemyIdle : public State {

	//Enemy AI Idle

public:

	static EnemyIdle *Instance();

	virtual void Enter(FSMObject * gameObject);

	virtual void Execute(FSMObject * gameObject);

	virtual void Exit(FSMObject * gameObject);

private:

	EnemyIdle() {}

	EnemyIdle(const EnemyIdle&);
	EnemyIdle& operator=(const EnemyIdle&);

};

class MoveToPositionTwo : public State {

	//enemy moves to position two

public:

	static MoveToPositionTwo *Instance();

	virtual void Enter(FSMObject * gameObject);

	virtual void Execute(FSMObject * gameObject);

	virtual void Exit(FSMObject * gameObject);


private:

	MoveToPositionTwo() {}

	MoveToPositionTwo(const MoveToPositionTwo&);

	MoveToPositionTwo& operator=(const MoveToPositionTwo&);

};

#endif // _ENEMYSTATES_H

