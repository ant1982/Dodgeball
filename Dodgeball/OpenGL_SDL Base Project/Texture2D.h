#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include <Windows.h>
#include <GL\glu.h>

class Texture2D {

private:

	GLuint _ID; //texture ID
	int _width, _height;

public:

	Texture2D();
	~Texture2D();

	bool LoadTextureTGA(const char* textureFileName);
	bool Load(char* path, int width, int height);

	GLuint GetID(); 
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }

	void BindTexture();

};

#endif //_TEXTURE2D_H
