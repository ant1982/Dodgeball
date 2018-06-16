#pragma once

#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Texture2D.h"

using namespace::std;

class TextureManager
{
public:
	
	~TextureManager();

	static TextureManager * GetInstance();

	void Loadtexture(string texturePath, int width, int height);

	void BindTexture(string name);

private:

	TextureManager();

	static TextureManager * mInstance;

	map<string, Texture2D *> textures;


};

#endif // _TEXTUREMANAGER_H

