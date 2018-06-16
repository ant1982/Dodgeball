#pragma once

#ifndef _DENZIL_H
#define _DENZIL_H

#include "GameObject.h"
#include <iostream>
#include <vector>

class Box;

class Denzil : public GameObject {

public:

	Denzil(string modelFileName);
	~Denzil();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

	virtual void loadTGAFile(char* path);

	void AddFollowingBalls(int numberOfHits);
	int ReturnHits() {return Hits;}

	bool ReachedExit();

	void SetExitReached();

	Box *GetBoundingBox();

protected:

private:

	Vector3D position;	
	Vector3D velocity;	
	Vector3D rotation;
	Vector3D mAcceleration;		
	Object3DS* meshAsset;
	Box * boundingBox;
	int Hits;
	float Zoffset;
	bool reachedExit;

};
#endif // _DENZIL_H

