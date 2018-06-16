#pragma once

#ifndef _GAMEOVERSCREEN
#define _GAMEOVERSCREEN

#include "GameScreen.h"
#include "GameScreenManager.h"

class GameOverScreen :  GameScreen
{
public:
	GameOverScreen(GameScreenManager * currentManager, int finalScore);
	~GameOverScreen();

	virtual void		Render();
	virtual void		Update(float deltaTime, SDL_Event e);
	void		OutputLine(float x, float y, string text);
	void		DrawHUD();
	

private:

	GameScreenManager*  CurrentManager;
	int playerScore;

};


#endif // !_GAMEOVERSCREEN

