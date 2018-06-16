#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameMenu.h"
#include "GameVictory.h"
#include "GameOverScreen.h"
#include "GameControls.h"
#include "Level1.h"


//--------------------------------------------------------------------------------------------------

GameScreenManager::GameScreenManager(SCREENS startScreen)
{
	currentScreen = NULL;

	//Ensure the first screen is set up.
	ChangeScreen(startScreen);
}

//--------------------------------------------------------------------------------------------------

GameScreenManager::~GameScreenManager()
{
	delete currentScreen;
	currentScreen = NULL;
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Render()
{
	currentScreen->Render();
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	currentScreen->Update(deltaTime, e);
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen.
	if (currentScreen != NULL && newScreen != SCREEN_GAMEOVER && newScreen != SCREEN_VICTORY)
	{
		delete currentScreen;
	}

	GameScreenLevel1* tempScreen1;
	GameMenu* tempMenuScreen;
	GameScreenLevel2* tempScreen2;
	GameOverScreen* tempGameOverScreen;
	GameVictory* tempWinScreen;
	GameControls* tempGameControls;
	
	int temp = 0;

	//Initialise the new screen.
	switch (newScreen)
	{
	case SCREEN_INTRO:
		break;

	case SCREEN_MENU:
		tempMenuScreen = new GameMenu(this);
		currentScreen = (GameScreen*)tempMenuScreen;
		tempMenuScreen = NULL;
		break;

	case SCREEN_LEVEL1:
		tempScreen1 = new GameScreenLevel1(this);
		currentScreen = (GameScreen*)tempScreen1;
		tempScreen1 = NULL;
		break;

	case SCREEN_LEVEL2:
		tempScreen2 = new GameScreenLevel2(this);
		currentScreen = (GameScreen*)tempScreen2;
		tempScreen2 = NULL;
		break;

	case SCREEN_GAMEOVER:
		temp = currentScreen->GetScore();
		if (currentScreen != NULL)
			delete currentScreen;
		tempGameOverScreen = new GameOverScreen(this, temp);
		currentScreen = (GameScreen*)tempGameOverScreen;
		tempGameOverScreen = NULL;
		break;

	case SCREEN_VICTORY:
		temp = currentScreen->GetScore();
		if (currentScreen != NULL)
			delete currentScreen;
		tempWinScreen = new GameVictory(this, temp);
		currentScreen = (GameScreen*)tempWinScreen;
		tempWinScreen = NULL;
		break;
	case SCREEN_GAMERULES:
		tempGameControls = new GameControls(this);
		currentScreen = (GameScreen*)tempGameControls;
		tempGameControls = NULL;
		break;
	}
}