#pragma once

#ifndef _SOUNDMANAGER_H
#define _SOUNDMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace::std;

class SoundManager
{
public:
	
	~SoundManager();

	static SoundManager * Instance();

	void LoadSound(string soundPath);

	void PlaySound(string name);

private:

	SoundManager();

	static SoundManager * instance;

	//need to create sound header and source GEC year 1

	// map<string, Texture2D *> sound;

};


#endif // _SOUNDMANAGER_H

