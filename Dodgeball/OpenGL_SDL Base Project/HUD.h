#pragma once

#ifndef _HUD_H
#define _HUD_H

#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include <string>

using namespace::std;

class HUD {

public:

	HUD();
	~HUD();

	virtual void Render();

protected:

	virtual void OutputLine(float x, float y, string text);

private:

};

#endif // _HUD_H

