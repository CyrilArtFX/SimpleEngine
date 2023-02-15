#pragma once
#include <map>
#include <string>
#include "Texture.h"
#include "Shader.h"
using std::map;
using std::string;

class Assets
{
public:
	static map<string, Texture> textures;
	static map<string, Shader> shaders;

	//  load a texture from file
	static Texture loadTexture(IRenderer& renderer, const string& filename, const string& name);
	//  retrieve a stored texture
	static Texture& getTexture(const string& name);


	//  load and generate a shader from file
	static Shader loadShader(const string& vShaderFile, const string& fShaderFile, const string& tcShaderFile,
		const string& teShaderFile, const string& gShaderFile, const string& name);
	//  retrieve a stored shader
	static Shader& getShader(const string& name);


	//  properly de-allocates all loaded resources
	static void clear();

private:
	Assets(){}

	//  load a single texture from file
	static Texture loadTextureFromFile(IRenderer& renderer, const string& filename);

	//  load and generate a shader from file
	static Shader loadShaderFromFile(const string& vShaderFile, const string& fShaderFile, 
		const string& tcShaderFile = "", const string& teShaderFile = "", const string& gShaderFile = "");
};

