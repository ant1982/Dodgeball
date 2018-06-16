#include "GameOverScreen.h"
#include "Constants.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"

GameOverScreen::GameOverScreen(GameScreenManager * currentManager, int finalScore) : GameScreen(){

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
	playerScore = finalScore;
	/*playerScore = 3;*/
}

GameOverScreen::~GameOverScreen() {

}

void GameOverScreen::Update(float deltaTime, SDL_Event e) {

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

void GameOverScreen::Render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	DrawHUD();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GameOverScreen::DrawHUD() {

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
	string temp = "Your Score was: " + to_string(playerScore);
	OutputLine(50, 50, temp);
	OutputLine(50, 75, "Game over!");
	OutputLine(50, 25, "Press Enter to return to main menu");
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void GameOverScreen::OutputLine(float x, float y, string text) {

	glRasterPos2f(x, y);  // where to start drawing
	for (int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}