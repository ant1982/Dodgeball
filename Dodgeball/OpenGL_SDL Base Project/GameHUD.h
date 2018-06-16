#pragma once

#pragma once

#ifndef _GAMEHUD_H
#define _GAMEHUD_H

class GameHUD {

private:
	GameHUD();
	int mValue;
	static GameHUD * mInstance;

public:
	static GameHUD * GetInstance();
	int GetValue();
	void IncrementValue(int amount);
};

#endif _GAMEHUD_H
