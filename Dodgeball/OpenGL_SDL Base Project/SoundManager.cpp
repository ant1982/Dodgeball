#include "SoundManager.h"

SoundManager * SoundManager::instance = 0;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

SoundManager * SoundManager::Instance() {

	if (!instance) {
		instance = new SoundManager();
	}
	return instance;
}

void SoundManager::LoadSound(string soundPath) {

}

void SoundManager::PlaySound(string name) {

}