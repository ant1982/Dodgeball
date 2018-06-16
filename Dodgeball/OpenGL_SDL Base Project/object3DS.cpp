#include "object3DS.h"
#include "../gl/glut.h"
#include "3DSLoader.h"

Object3DS::Object3DS(Vector3D startPosition, string modelFileName) {

	//start position
	mPosition = startPosition;

	//3DS file to load
	std::strcpy(fileName, modelFileName.c_str());
	loadModel();
	/*loadTexture();*/



}

void Object3DS::loadModel() {

	if (fileName[0] != '---')
	{
		Load3DS(&object, fileName);
	}
}

void Object3DS::loadTexture(char* path, int width, int height) {


	glLoadIdentity();
	Texture2D* mtexture = new Texture2D();
	mtexture->Load(path, width, height);
	object.id_texture = mtexture->GetID();
	//glBindTexture(GL_TEXTURE_2D, mtexture->GetID());
}

void Object3DS::loadTGAFile(char* path) {

	glLoadIdentity();
	Texture2D* mtexture = new Texture2D();
	mtexture->LoadTextureTGA(path);
	object.id_texture = mtexture->GetID();
}

void Object3DS::Update(float deltaTime) {

}

void Object3DS::Render() {


	glPushMatrix();
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, object.id_texture); //we set the active texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_TRIANGLES); //delimit the vertices that define a primitive (triangles)

	for (int l_index = 0; l_index < object.polygons_qty; l_index++)
	{
		/*Texture Coordinates of the first vertex*/
		glTexCoord2f(object.mapcoord[object.polygon[l_index].a].u,
			object.mapcoord[object.polygon[l_index].a].v);

		//coordinates of the first vertex

		glVertex3f(object.vertex[object.polygon[l_index].a].x,
			object.vertex[object.polygon[l_index].a].y,
			object.vertex[object.polygon[l_index].a].z);

		//Texture Coordinates of the second vertex
		glTexCoord2f(object.mapcoord[object.polygon[l_index].b].u,
			object.mapcoord[object.polygon[l_index].b].v);

		//coordinates of the second vertex

		glVertex3f(object.vertex[object.polygon[l_index].b].x,
			object.vertex[object.polygon[l_index].b].y,
			object.vertex[object.polygon[l_index].b].z);

		//Texture Coordinates of the third vertex
		glTexCoord2f(object.mapcoord[object.polygon[l_index].c].u,
			object.mapcoord[object.polygon[l_index].c].v);

		//coordinates of the third vertex

		glVertex3f(object.vertex[object.polygon[l_index].c].x,
			object.vertex[object.polygon[l_index].c].y,
			object.vertex[object.polygon[l_index].c].z);
	}
	glEnd();

	glPopMatrix();
}