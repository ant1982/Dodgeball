#pragma once

#ifndef _STATE_H
#define _STATE_H

class FSMObject;

class State
{
public:	
	virtual ~State(){}

	virtual void Enter(FSMObject*) = 0;
	virtual void Exit(FSMObject*) = 0;
	virtual void Execute(FSMObject *) = 0;

private:

	

	//State* mCurrentState;
	//enum STATE {STATE_NONE};
};

#endif // _STATE_H
