#pragma once

#ifndef _WINZONE_H
#define _WINZONE_H

#include "GameObject.h"

class Sphere;

class WinZone : GameObject
{
public:
	WinZone(Vector3D finishPosition);
	~WinZone();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	Sphere * GetBoundingSphere();

private:

	Vector3D mPosition;
	Sphere * boundingSphere;
	float radius;

};


#endif // !_WINZONE_H

