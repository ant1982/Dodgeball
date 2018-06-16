#pragma once

#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H

#include <SDL.h>
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Texture2D.h"
#include "object3DS.h"
#include "Denzil.h"
#include "Camera.h"
#include "Court.h"
#include "FSMObject.h"

class GameScreenLevel2: public GameScreen
{
public:
	GameScreenLevel2(GameScreenManager * currentManager);
	~GameScreenLevel2();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

	void		SetMaterial();
	void		SetLight();
	void		EnableLights();
	void		DrawHUD();
	void		OutputLine(float x, float y, string text);

private:

	Denzil * player;
	FSMObject * testObject;
	Court * level2court;
	GameScreenManager*  CurrentManager;
	int playerHits;
	float level2Time;

};

#endif _GAMESCREENLEVEL2_H

