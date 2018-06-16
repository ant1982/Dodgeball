#pragma once

#ifndef _GAMECONTROLS_H
#define _GAMECONTROLS_H

#include <SDL.h>
#include "GameScreen.h"
#include "MenuHUD.h"
#include <vector>
#include <string>

using namespace std;

class GameScreenManager;

class GameControls : public GameScreen {

public:

	GameControls(GameScreenManager * currentManager);
	~GameControls();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void		DrawHUD();
	void		OutputLine(float x, float y, string text);

private:

	GameScreenManager*  CurrentManager;

};

#endif // _GAMECONTROLS_H
