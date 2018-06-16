#pragma once

#include "GameObject.h"
#include <iostream>

using namespace std;

#ifndef _DODGEBALL_H
#define _DODGEBALL_H

using namespace std;


class Sphere;

class Dodgeball : public GameObject {

public:

	Dodgeball(string modelFileName);
	~Dodgeball();

	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void loadTGAFile(char* path);
	void Respawn();

	Sphere * GetBoundingSphere();

protected:

private:

	Vector3D position;
	float scale;
	Vector3D velocity;
	Sphere * boundingSphere;
	Vector3D rotation;
	Vector3D mAcceleration;
	float restitution;
	Object3DS* BallAsset;
	bool Collided;
};

#endif // _DODGEBALL_H
