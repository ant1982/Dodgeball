#include "Court.h"
#include "Collision.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <SDL_mixer.h>

Mix_Chunk * bounce1 = NULL;

Court::Court(string modelFileName) : GameObject() {

	std::strcpy(fileName, modelFileName.c_str());

	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;

	courtAsset = new Object3DS(Vector3D(position), modelFileName);
	surface = new Plane(position);

	bounce1 = Mix_LoadWAV("Bounce.wav");
	if (bounce1 == NULL)
	{
		cout << "Failed to load scratch sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
	}
}

Court::~Court(){

	delete courtAsset;
}

void Court::Update(float deltaTime) {

	surface->SetCollided(false);
}

void Court::Render() {

	if(surface->GetCollided()) {
		Mix_PlayChannel(-1, bounce1, 0);
	}

	courtAsset->Render();
}

void Court::loadTGAFile(char* path) {

	courtAsset->loadTGAFile(path);
}

Plane * Court::GetSurface() {
	return surface;
}