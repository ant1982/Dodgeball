#pragma once

#ifndef _ENEMYATTACK_H
#define _ENEMYATTACK_H

#include "GameObject.h"
#include <iostream>
using namespace std;

class Sphere;
class Denzil;

class EnemyAttack : public GameObject {

public:

	EnemyAttack(Denzil * target ,Vector3D spawnLoc);
	~EnemyAttack();

	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void loadTGAFile(char* path);
	bool OutOfBounds();
	

	Sphere * GetBoundingSphere();

private:

	Vector3D position;
	float scale;
	bool outOfBounds;
	
	Vector3D velocity;
	Sphere * boundingSphere;
	Vector3D rotation;
	Vector3D mAcceleration;
	Denzil * playerTarget;
	

};

#endif // !_ENEMYATTACK_H

