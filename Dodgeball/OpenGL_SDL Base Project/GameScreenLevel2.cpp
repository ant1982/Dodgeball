#include "GameScreenLevel2.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Camera.h"
#include <stdio.h>
#include <SDL_mixer.h>
#include <iostream>

clock_t level2 = NULL;
float level2Time = 0.0f;

Mix_Chunk * gameOver2 = NULL;
Mix_Chunk * winSound2 = NULL;

GameScreenLevel2::GameScreenLevel2(GameScreenManager * currentManager) : GameScreen()
{
	float level2Time = 0.0f;
	level2 = clock();
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
	EnableLights();
	glEnable(GL_NORMALIZE);

	//clear background colour.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//--------------------------------------------------------------------------------------------------

	/*robotHUD = new HUD();*/

	CurrentManager = currentManager;

	level2court = new Court("newCourt.3ds");
	level2court->loadTGAFile("Court.tga");
	player = new Denzil("Denzil2.3ds");
	testObject = new FSMObject("Denzil2.3ds",player);

	gameOver2 = Mix_LoadWAV("Scream.wav");
	if (gameOver2 == NULL)
	{
		cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError();
	}
	winSound2 = Mix_LoadWAV("Jingle.wav");
	if (winSound2 == NULL)
	{
		cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError();
	}

	playerHits = 0;
}

GameScreenLevel2::~GameScreenLevel2()
{

}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e) {

	level2Time = (clock() - level2) / CLOCKS_PER_SEC;
	Camera::GetInstance()->Update(deltaTime, e);

	level2court->Update(deltaTime);
	player->Update(deltaTime, e);
	testObject->Update(deltaTime);

	playerHits = player->ReturnHits();	

	if (player->ReachedExit())
	{
		Mix_PlayChannel(-1, winSound2, 0);
		SDL_Delay(500);
		score = (100 - (int)level2Time * playerHits);
		CurrentManager->ChangeScreen(SCREEN_VICTORY);
	}
	else

		if (player->ReturnHits() == 4)
		{
			Mix_PlayChannel(-1, gameOver2, 0);
			SDL_Delay(500);
			playerHits = player->ReturnHits();
			score = (100 - (int)level2Time * playerHits);
			CurrentManager->ChangeScreen(SCREEN_GAMEOVER);
		}
}

void GameScreenLevel2::Render() {

	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	//glPushMatrix();
	Camera::GetInstance()->Render();	
	DrawHUD();
	SetLight();
	SetMaterial();

	level2court->Render();
	player->Render();
	testObject->Render();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GameScreenLevel2::SetLight() {

	lighting light = {
		{ 0.2f, 0.2f, 0.2f, 1.0f },
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	};
	// position of the light in homogeneous coordinates (x, y, z, w)
	// w should be 0 for directional lights, and 1 for spotlights
	float light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	lighting light2 = {
		{ 0.0f, 0.0f, 0.5f, 1.0f },
		{ 0.0f, 0.0f, 0.5f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	};
	float light_pos2[] = { -1.0f,-1.0f,-1.0f,0.0f };

	//glLightfv(GL_LIGHT1, GL_AMBIENT, light2.ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light2.diffuse);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, light2.specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);
}

void GameScreenLevel2::SetMaterial() {

	material material = {
		{ 0.80f, 0.05f, 0.05f, 1.0f },
		{ 0.80f, 0.05f, 0.05f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		100.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}

void GameScreenLevel2::EnableLights() {

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void GameScreenLevel2::DrawHUD() {

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
	string temp = "Time: " + to_string((int)level2Time);
	OutputLine(5, 95, temp);
	OutputLine(80, 95, "Times hit: " + to_string(playerHits));

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void GameScreenLevel2::OutputLine(float x, float y, string text) {

	glRasterPos2f(x, y);  // where to start drawing
	for (int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}