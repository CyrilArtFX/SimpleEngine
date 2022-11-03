#pragma once
#include <SDL.h>
#include "Actor.h"

class Window;
struct Rectangle;
struct Vector2;

class Renderer
{
public:
	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL
	};

	Renderer();
	~Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }

	bool initialize(Window& window);
	void beginDraw();
	void draw();
	void endDraw();
	void close();

	void setCamPos(Vector2 camPosP);

	void drawRect(const Rectangle& rect);
	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprites();
	void drawSprite(const Actor& actor, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const;

private:
	SDL_Renderer* SDLRenderer{ nullptr };
	std::vector<SpriteComponent*> sprites;
	Vector2 camPos{ Vector2::zero };
};

