#pragma once

#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <Windows.H>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Commons.h"
#include <SDL.h>
#include "Texture2D.h"
#include "object3DS.h"
#include "Collision.h"

class GameObject {

public:

	GameObject();
	~GameObject();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();
	virtual void loadTGAFile(char* path);

protected:

	char fileName[20];

private:

	Vector3D mPosition;
	Vector3D mRotation;
	Vector3D mScale;
	Vector3D mVelocity;
	

};

#endif // _GAMEOBJECT_H