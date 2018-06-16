#include "TextureManager.h"

TextureManager * TextureManager::mInstance = 0;

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {

}

void TextureManager::BindTexture(string name) {

	//retrieve texture object from map using its key.
	//pointer to texture2D->BindTexture

	//if key not in map call load texture() to create map object
	//then call pointer to texture2D->BindTexture
}

void TextureManager::Loadtexture(string texturePath, int width, int height) {

	if (Texture2D * texturePath = textures.find("texturePath")->second) //check for key entry
	{
		cout << "entry already exists" << endl;
	}
	else
	{
		//construct new Texture Object and call load method
		//store pointer in map and use texture path string as key
	}
}

TextureManager * TextureManager::GetInstance() {

	if (!mInstance) {
		mInstance = new TextureManager();
	}
	return mInstance;
}