#include "GameMenu.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Camera.h"
#include <iostream>
#include "GameScreenManager.h"

using namespace::std;

GameMenu::GameMenu(GameScreenManager * currentManager): GameScreen() {


	mMenuItems.push_back("Level 1");
	mMenuItems.push_back("Level 2");
	mMenuItems.push_back("Rules and controls");
	mMenuItems.push_back("Exit");

	if (mMenuItems.size() != 0)
	{
		selected = MENU_LEVEL1;
	}

	mInstructions.push_back("Use arrow keys to navigate menu");
	mInstructions.push_back("Enter to select");

	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal
	
	glEnable(GL_NORMALIZE);

	//clear background colour.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	CurrentManager = currentManager;
}

GameMenu::~GameMenu() {
		
	mInstructions.clear();
}

void GameMenu::Render() {

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);

	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int i;
	for (i = 0; i< mMenuItems.size(); i++)
	{
		if (i == selected) {
			glColor3f(1.0f, 0.4f, 0.0f);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
		}
		OutputLine(30, 80 - 10 * i, mMenuItems[i]);
	}
	for (int j = 0; j < mInstructions.size(); j++) {
		glColor3f(0.0, 0.0, 0.0);
		OutputLine(20, 70 - 10 * j - 10 * i, mInstructions[j]);
	}

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();	
}

void GameMenu::Update(float deltaTime, SDL_Event e) {
	
	HandleInput(e);
}

void GameMenu::HandleInput(SDL_Event e)
{
	switch (e.type) {
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			if (selected > 0) {
				selected = selected - 1;
			}
			break;
		case SDLK_DOWN:
			if (selected < mMenuItems.size() - 1)
			{
				selected++;
			}
			break;

		case SDLK_RETURN:
			HandleSelectedItem();
			break;

		default:
			break;
		}
	}
}

void GameMenu::HandleSelectedItem() {

	if (selected == 0)
	{
		CurrentManager->ChangeScreen(SCREEN_LEVEL1);
	}
	else if (selected == 1)
	{
		CurrentManager->ChangeScreen(SCREEN_LEVEL2);
	}
	else if (selected == 2)
	{
		CurrentManager->ChangeScreen(SCREEN_GAMERULES);
	}
	else if (selected == 3)
	{
		SDL_Event sdlevent;
		sdlevent.type = SDL_QUIT;
		SDL_PushEvent(&sdlevent);
	}
}

void GameMenu::OutputLine(float x, float y, string text) {

	glRasterPos2f(x, y);  // where to start drawing
	for (int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}
