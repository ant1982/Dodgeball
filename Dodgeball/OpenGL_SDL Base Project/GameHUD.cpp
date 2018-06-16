#include "GameHUD.h"

GameHUD * GameHUD::mInstance = 0;

GameHUD::GameHUD() {

	mValue = 0;
}

GameHUD*GameHUD::GetInstance() {

	if (!mInstance)
	{
		mInstance = new GameHUD();
	}
	return mInstance;
}

int GameHUD::GetValue() {

	return mValue;
}

void GameHUD::IncrementValue(int amount) {

	mValue += amount;
}