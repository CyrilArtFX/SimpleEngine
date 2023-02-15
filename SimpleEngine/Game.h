#pragma once
#include <vector>
#include "Window.h"
#include "RendererSDL.h"
#include "RendererOGL.h"
#include "Vector2.h"
#include "Assets.h"
#include "SpriteComponent.h"
#include "Obstacle.h"
#include "RoadCollider.h"
#include "Player.h"
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
	//RendererSDL& getRenderer() { return renderer; }
	RendererOGL& getRenderer() { return renderer; }

	vector<Obstacle*>& getObstacles();
	void addObstacle(Obstacle* obstacle);
	void removeObstacle(Obstacle* obstacle);

	vector<RoadCollider*>& getRoadColliders();
	void addRoadCollider(RoadCollider* roadCollider);
	void removeRoadCollider(RoadCollider* roadCollider);

	Player* getPlayer() const { return player; }

private:
	void processInput();
	void update(float dt);
	void render();

	Window window;
	//RendererSDL renderer;
	RendererOGL renderer;
	bool isRunning{ true };

	Player* player{ nullptr };
	bool isUpdatingActors{ false };
	vector<Actor*> actors;
	vector<Actor*> pendingActors;
	vector<Obstacle*> obstacles;
	vector<RoadCollider*> roadColliders;
};

