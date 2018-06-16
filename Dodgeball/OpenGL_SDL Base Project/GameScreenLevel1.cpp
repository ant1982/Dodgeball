#include "GameScreenLevel1.h"
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

using namespace::std;

Mix_Chunk * gameOver = NULL;
Mix_Chunk * winSound = NULL;
clock_t beginTime = NULL;
float currentTime = 0.0f;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1(GameScreenManager * currentManager) : GameScreen()
{
	float currentTime = 0.0f;
	beginTime = clock();
	srand(time(NULL));
	
	glEnable(GL_DEPTH_TEST);

	//initialise hitcounter
	numberOfHits = 0;
	//initialise score
	score = 0;
	playerDead = false;

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f,aspect,0.1f,1000.0f);

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

	newCourt = new Court("newCourt.3ds");
	newCourt->loadTGAFile("Court.tga");

	denzil = new Denzil("Denzil2.3ds");

	
	
	gameOver = Mix_LoadWAV("Scream.wav");
	if (gameOver == NULL)
	{
		cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError();
	}
	winSound = Mix_LoadWAV("Jingle.wav");
	if (winSound == NULL)
	{
		cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError();
	}

	for (int i = 0; i < 10; i++) {
		dodgeBalls.push_back(new Dodgeball("Dodgeball1.3ds"));
	}

	for (int i = 0; i < dodgeBalls.size(); i++) {
		dodgeBalls[i]->loadTGAFile("dodgeballtexture.tga");
	}
}

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::~GameScreenLevel1()
{	
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	//glPushMatrix();
	Camera::GetInstance()->Render();
	DrawHUD();

	/*robotHUD->Render();*/

	SetLight();
	SetMaterial();

	newCourt->Render();
	denzil->Render();


	for (int i = 0; i < dodgeBalls.size(); i++) {
		dodgeBalls[i]->Render();
	}
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{		
	Camera::GetInstance()->Update(deltaTime, e);	
	currentTime = (clock() - beginTime) / CLOCKS_PER_SEC;	

	newCourt->Update(deltaTime);
	denzil->Update(deltaTime,e);

	//check for win condition
	if (denzil->ReachedExit())
	{
		Mix_PlayChannel(-1, winSound, 0);
		SDL_Delay(500);
		score = (100 - (int)currentTime * numberOfHits);
		CurrentManager->ChangeScreen(SCREEN_VICTORY);
	}
	else
	{
		for (int i = 0; i < dodgeBalls.size(); i++) {
			dodgeBalls[i]->Update(deltaTime);
		}

		// check for collisions
		for (int i = 0; i < dodgeBalls.size() - 1; i++) {
			for (int j = i + 1; j < dodgeBalls.size(); j++) {
				Collision::SphereSphereCollision(dodgeBalls[i]->GetBoundingSphere(), dodgeBalls[j]->GetBoundingSphere());
			}
		}

		for (int i = 0; i < dodgeBalls.size() - 1; i++) {
			for (int j = i + 1; j < dodgeBalls.size(); j++) {
				Collision::SpherePlaneCollision(dodgeBalls[i]->GetBoundingSphere(), newCourt->GetSurface());
			}
		}

		// check for player collisions with dodgeballs

		for (int i = 0; i < dodgeBalls.size(); i++) {
			if (Collision::BoxCircleCollision(denzil->GetBoundingBox(), dodgeBalls[i]->GetBoundingSphere()))
			{
				dodgeBalls[i]->Respawn();
				numberOfHits++;
				denzil->AddFollowingBalls(numberOfHits);
				if (numberOfHits >= 4)
				{
					playerDead = true;
					Mix_PlayChannel(-1, gameOver, 0);
					SDL_Delay(500);
					score = (100 - (int)currentTime * numberOfHits);
					CurrentManager->ChangeScreen(SCREEN_GAMEOVER);
				}
			}
		}
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_x:
				CurrentManager->ChangeScreen(SCREEN_MENU);
				break;

			default:
				break;
			}
		}
	}
}

void GameScreenLevel1::SetLight() {
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

void GameScreenLevel1::SetMaterial() {
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

void GameScreenLevel1::OutputLine(float x, float y, string text) {
	
	glRasterPos2f(x, y);  // where to start drawing
	for (int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}

void GameScreenLevel1::DrawHUD() {

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
	string temp = "Time: " + to_string((int)currentTime);
	OutputLine(5, 95, temp);
	OutputLine(80, 95, "Times hit: " + to_string(numberOfHits));
		
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void GameScreenLevel1::EnableLights() {
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}


//--------------------------------------------------------------------------------------------------

