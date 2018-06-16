#pragma once

#ifndef _MENUHUD_H
#define _MENUHUD_H

#include "HUD.h"
#include <vector>

class MenuHUD: HUD
{
public:
	MenuHUD();
	~MenuHUD();

	virtual void Render();

protected:

	virtual void OutputLine(float x, float y, string text);

private:

};

#endif // _MENUHUD_H

