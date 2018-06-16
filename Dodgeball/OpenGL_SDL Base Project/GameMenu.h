#pragma once

#ifndef _GAMEMENU_H
#define _GAMEMENU_H

#include <SDL.h>
#include "GameScreen.h"
#include "MenuHUD.h"
#include <vector>
#include <string>

using namespace std;

#define MENU_NONE	-1
#define MENU_LEVEL1 0
#define MENU_LEVEL2 1
#define MENU_EXIT	2

class GameScreenManager;

class GameMenu: public GameScreen
{
public:
	GameMenu(GameScreenManager * currentManager);
	~GameMenu();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void		OutputLine(float x, float y, string text);

protected:
	void HandleInput(SDL_Event e);
	vector<string> mInstructions;
	vector<string>mMenuItems;

private:


	int selected = MENU_NONE;
	void HandleSelectedItem();

	GameScreenManager * CurrentManager;
};

#endif // _GAMEMENU_H

