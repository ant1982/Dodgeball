#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Texture2D.h"
#include "object3DS.h"
#include "Camera.h"
#include "RobotBaseClass.h"
#include "RobotUpperArm.h"
#include "RobotLowerArm.h"
#include "RobotHand.h"
#include "HUD.h"
#include "GameScreenManager.h"
#include "Dodgeball.h"
#include "Court.h"
#include "Denzil.h"
#include "WinZone.h"
#include <vector>

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1(GameScreenManager * currentManager);
	~GameScreenLevel1();

	/*bool		SetUpLevel();*/
	virtual void		Render();
	virtual void		Update(float deltaTime, SDL_Event e);
	void		SetMaterial();
	void		SetLight();

	void		OutputLine(float x, float y, string text);

	void		DrawHUD();
	void		EnableLights();
	int		GetScore() { return score; }

//--------------------------------------------------------------------------------------------------
private:


	GameScreenManager*  CurrentManager;
	Court * newCourt;
	Denzil * denzil;

	vector<Dodgeball *> dodgeBalls;
	float mCurrentTime;
	int numberOfHits;
	int score;
	bool playerDead;
};


#endif //_GAMESCREENLEVEL1_H