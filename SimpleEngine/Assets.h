#pragma once
#include <map>
#include <string>
#include "Texture.h"
using std::map;
using std::string;

class Assets
{
public:
	static map<string, Texture> textures;

	//  load a texture from file
	static Texture loadTexture(Renderer& renderer, const string& filename, const string& name);

	//  retrieve a stored texture
	static Texture& getTexture(const string& name);

	//  properly de-allocates all loaded resources
	static void clear();

private:
	Assets(){}

	//  load a single texture from file
	static Texture loadTextureFromFile(Renderer& renderer, const string& filename);
};

