#pragma once
#include <string>
#include "Renderer.h"
using std::string;

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	bool load(Renderer& rendererP, const string& filenameP);
	SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heightOut);

	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	string filename{ "" };
	SDL_Texture* SDLTexture{ nullptr };
	int width{ 0 };
	int height{ 0 };
};

