#ifndef _OBJECT3DS_H_
#define _OBJECT3DS_H_

#include "Commons.h"
#include "string"
#include "Texture2D.h"

using std::string;

class Object3DS
{
public:
	Object3DS(Vector3D startposition, string modelFileName);
	~Object3DS() {}

	void Update(float deltaTime);
	void Render();

	//load 3DS file
	void loadModel();

	void loadTexture(char* path, int width, int height);
	void loadTGAFile(char*path);

private:
	Vector3D mPosition;
	Texture2D* mtexture;

	char fileName[20];
	char textureName[20];

	obj_type object;
	GLuint texID;
};

#endif //_OBJECT3DS_H_


