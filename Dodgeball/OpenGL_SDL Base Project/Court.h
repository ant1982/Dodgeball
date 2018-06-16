#pragma once

#include "GameObject.h"
#include <iostream>

#ifndef _COURT_H
#define _DODGEBALL_H

using namespace std;


class Plane;

class Court : public GameObject {

public:

	Court(string modelFileName);
	~Court();

	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void loadTGAFile(char* path);

	Plane * GetSurface();

protected:

private:

	Vector3D position;
	Plane * surface;
	Object3DS* courtAsset;
};

#endif // _DODGEBALL_H
