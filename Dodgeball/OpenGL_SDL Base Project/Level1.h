#pragma once

#ifndef _LEVEL1_H
#define _LEVEL1_H

#include "GameScreen.h"
#include <iostream>
#include "GameScreenManager.h"

using namespace::std;

class Level1 : GameScreen {

public:

	Level1(GameScreenManager * currentManager);
	~Level1();

	virtual void		Render();
	virtual void		Update(float deltaTime, SDL_Event e);

protected:

private:

	GameScreenManager * CurrentManager;

};
#endif // _LEVEL1_H

