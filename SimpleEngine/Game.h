#pragma once
#include <vector>
#include "Window.h"
#include "RendererOGL.h"
#include "Assets.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "InputSystem.h"
using std::vector;

class Game
{
	// Begin SINGLETON
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() = default;
	// End SINGLETON

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	RendererOGL& getRenderer() { return renderer; }

	Player* getPlayer() const { return player; }

	void changeCamera(int mode);

private:
	void processInput();
	void update(float dt);
	void render();

	Window window;
	RendererOGL renderer;
	InputSystem inputSystem;
	bool isRunning{ true };
	bool isUpdatingActors{ false };

	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	Player* player{ nullptr };
	class FPSActor* fps{ nullptr };
	class FollowActor* follow{ nullptr };
	class SpriteComponent* crosshair{ nullptr };
};

