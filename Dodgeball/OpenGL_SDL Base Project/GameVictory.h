#pragma once

#ifndef _GAMEVICTORY_H
#define _GAMEVICTORY_H

#include "GameScreen.h"
#include "GameScreenManager.h"

class GameVictory : GameScreen
{
public:
	GameVictory(GameScreenManager * currentManager, int finalScore);
	~GameVictory();

	virtual void		Render();
	virtual void		Update(float deltaTime, SDL_Event e);
	void		OutputLine(float x, float y, string text);
	void		DrawHUD();


private:

	GameScreenManager*  CurrentManager;
	int playerScore;

};

#endif //_GAMEVICTORY_H