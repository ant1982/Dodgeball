#include "GameControls.h"
#include "GameScreenManager.h"
#include "Constants.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"

GameControls::GameControls(GameScreenManager * currentManager) : GameScreen() {

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

GameControls::~GameControls() {

}

void GameControls::Render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	DrawHUD();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GameControls::Update(float deltaTime, SDL_Event e) {

	switch (e.type) {
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {

		case SDLK_RETURN:
			CurrentManager->ChangeScreen(SCREEN_MENU);
			break;

		default:
			break;
		}
	}
}

void GameControls::DrawHUD() {
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glColor3f(1.0, 1.0, 1.0);
	OutputLine(45, 95, "Game Controls");
	OutputLine(45, 85, "Move Forward:  W");
	OutputLine(45, 80, "Move Backward: S");
	OutputLine(45, 75, "Move Left: A");
	OutputLine(45, 70, "Move Left: D");
	OutputLine(35, 60, "Level 1: avoid the dodgeballs and reach the far side");
	OutputLine(35, 55, "Level 2: avoid the AI attacks and reach the other side");

	OutputLine(35, 25, "Press Enter to return to main menu");
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}

void GameControls::OutputLine(float x, float y, string text) {

	glRasterPos2f(x, y);  // where to start drawing
	for (int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}
