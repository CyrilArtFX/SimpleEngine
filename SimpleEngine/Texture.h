#pragma once
#include <string>
#include "IRenderer.h"
#include "RendererSDL.h"
#include "RendererOGL.h"
using std::string;

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	bool loadSDL(RendererSDL& rendererP, const string& filenameP);
	bool loadOGL(RendererOGL& rendererP, const string& filenameP);

	SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heightOut);
	void setActive() const;

	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	unsigned int textureID;
	string filename{ "" };
	SDL_Texture* SDLTexture{ nullptr };
	int width{ 0 };
	int height{ 0 };
};

