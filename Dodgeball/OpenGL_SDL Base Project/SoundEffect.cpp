#include "SoundEffect.h"

SoundEffect::SoundEffect() {

}

SoundEffect::~SoundEffect() {

}

void SoundEffect::LoadMusic(string filePath) {

	gMusic = Mix_LoadMUS(filePath.c_str());
	if (gMusic == NULL)
	{
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}
}

void SoundEffect::PlayMusic() {

}