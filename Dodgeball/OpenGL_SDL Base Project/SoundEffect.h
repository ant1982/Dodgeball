#pragma once

#ifndef _SOUNDEFFECT_H
#define _SOUNDEFFECT_H

#include <string>
#include <SDL_mixer.h>
#include <iostream>

using namespace::std;

class SoundEffect {

public:

	SoundEffect();
	~SoundEffect();

	void LoadMusic(string filePath);

	void PlayMusic();

private:

	Mix_Music* gMusic = NULL;

};

#endif // _SOUNDEFFECT_H

