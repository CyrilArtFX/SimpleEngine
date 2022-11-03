#include "Game.h"
#include "Timer.h"
#include "Player.h"
#include "RaceTimer.h"

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	return isWindowInit && isRendererInit;
}

void Game::load()
{
	//  load textures
	Assets::loadTexture(renderer, "RacingGame/Car.png", "car");
	Assets::loadTexture(renderer, "RacingGame/Obstacle.png", "obstacle");
	Assets::loadTexture(renderer, "RacingGame/background.png", "background");

	//  load actors
    player = new Player();
	player->setPosition(Vector2{ -300, -500 });
	Vector2 playerPos = player->getPosition();
	renderer.setCamPos(Vector2(playerPos.x - WINDOW_WIDTH / 2, playerPos.y - WINDOW_HEIGHT / 2));

	auto background = new Actor();
	auto sc = new SpriteComponent(background, Assets::getTexture("background"), 10);

	new RaceTimer();


	//  obstacles
	new Obstacle(Vector2{ 200.0f, -560.0f }, Vector2{ 200.0f, -440.0f });
	new Obstacle(Vector2{ 960.0f, -240.0f }, Vector2{ 1080.0f, -360.0f });
	new Obstacle(Vector2{ 600.0f, 440.0f }, Vector2{ 600.0f, 560.0f });
	new Obstacle(Vector2{ -300.0f, 40.0f }, Vector2{ -300.0f, 160.0f });
	new Obstacle(Vector2{ -640.0f, -300.0f }, Vector2{ -520.0f, -300.0f });

	//  road colliders
	new RoadCollider(Rectangle{ -670.0f, -575.0f, 1140.0f, 140.0f });
	new RoadCollider(Rectangle{ 330.0f, -375.0f, 740.0f, 140.0f });
	new RoadCollider(Rectangle{ -70.0f, 425.0f, 1140.0f, 140.0f });
	new RoadCollider(Rectangle{ -1070.0f, 25.0f, 1140.0f, 140.0f });
	new RoadCollider(Rectangle{ -1070.0f, -175.0f, 540.0f, 140.0f });
	new RoadCollider(Rectangle{ 330.0f, -435.0f, 140.0f, 60.0f });
	new RoadCollider(Rectangle{ 930.0f, -235.0f, 140.0f, 660.0f });
	new RoadCollider(Rectangle{ -70.0f, 125.0f, 140.0f, 360.0f });
	new RoadCollider(Rectangle{ -1070.0f, -35.0f, 140.0f, 60.0f });
	new RoadCollider(Rectangle{ -670.0f, -435.0f, 140.0f, 260.0f });
}

void Game::loop()
{
	Timer timer;
	float dt = 0;

	while (isRunning) 
	{
		dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::unload()
{
	while (!actors.empty())
	{
		//delete actors.back();  //  not understood why but it causes an error when closing the window
		actors.pop_back();  //  so I use this instead, I think it's not the correct way to do this but it doesn't causes an error
	}


	Assets::clear();
}

void Game::close()
{
	window.close();
	SDL_Quit();
}

void Game::processInput()
{
	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}

	// Keyboard state
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	// Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}

	//  actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(keyboardState);
	}
	isUpdatingActors = false;
}

void Game::update(float dt)
{
	//  update actors
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	//  move penfing actors to actors
	for (auto pendingActor : pendingActors)
	{
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	//  delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}

	Vector2 playerPos = player->getPosition();
	renderer.setCamPos(Vector2(playerPos.x - WINDOW_WIDTH / 2, playerPos.y - WINDOW_HEIGHT / 2));
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}

	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(pendingActors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}

void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

vector<Obstacle*>& Game::getObstacles()
{
	return obstacles;
}

void Game::addObstacle(Obstacle* obstacle)
{
	obstacles.emplace_back(obstacle);
}

void Game::removeObstacle(Obstacle* obstacle)
{
	auto iter = std::find(begin(obstacles), end(obstacles), obstacle);
	if (iter != obstacles.end())
	{
		obstacles.erase(iter);
	}
}

vector<RoadCollider*>& Game::getRoadColliders()
{
	return roadColliders;
}

void Game::addRoadCollider(RoadCollider* roadCollider)
{
	roadColliders.emplace_back(roadCollider);
}

void Game::removeRoadCollider(RoadCollider* roadCollider)
{
	auto iter = std::find(begin(roadColliders), end(roadColliders), roadCollider);
	if (iter != roadColliders.end())
	{
		roadColliders.erase(iter);
	}
}