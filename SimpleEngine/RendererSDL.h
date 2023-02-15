#pragma once
#include <SDL.h>
#include "IRenderer.h"
#include "Actor.h"
#include "Rectangle.h"

class Window;
struct Rectangle;
struct Vector2;

class RendererSDL : public IRenderer
{
public:
	RendererSDL();
	virtual ~RendererSDL();
	RendererSDL(const RendererSDL&) = delete;
	RendererSDL& operator=(const RendererSDL&) = delete;

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
	IRenderer::Type type() { return Type::SDL; }

private:
	SDL_Renderer* SDLRenderer{ nullptr };
	std::vector<SpriteComponent*> sprites;
	Vector2 camPos{ Vector2::zero };
};

