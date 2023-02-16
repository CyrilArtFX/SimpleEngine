#include "Game.h"
#include "Timer.h"
#include "Player.h"
#include "MeshComponent.h"
#include "Cube.h"
#include "Sphere.h"
#include "Plane.h"
#include "FPSActor.h"
#include "FollowActor.h"

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	bool isInputInit = inputSystem.initialize();
	return isWindowInit && isRendererInit && isInputInit;
}

void Game::load()
{
	//  load textures
	Assets::loadTexture(renderer, "RacingGame/Car.png", "car");
	/*Assets::loadTexture(renderer, "RacingGame/Obstacle.png", "obstacle");
	Assets::loadTexture(renderer, "RacingGame/background.png", "background");
	Assets::loadShader("Shaders/Basic.vert", "Shaders/Basic.frag", "", "", "", "Basic");
	Assets::loadShader("Shaders/Transform.vert", "Shaders/Basic.frag", "", "", "", "Transform");*/
	Assets::loadShader("Shaders/Sprite.vert", "Shaders/Sprite.frag", "", "", "", "Sprite");
	Assets::loadShader("Shaders/BasicMesh.vert", "Shaders/BasicMesh.frag", "", "", "", "BasicMesh");
	Assets::loadShader("Shaders/Phong.vert", "Shaders/Phong.frag", "", "", "", "Phong");

	Assets::loadTexture(renderer, "Res/Textures/Default.png", "Default");
	Assets::loadTexture(renderer, "Res/Textures/Cube.png", "Cube");
	Assets::loadTexture(renderer, "Res/Textures/HealthBar.png", "HealthBar");
	Assets::loadTexture(renderer, "Res/Textures/Plane.png", "Plane");
	Assets::loadTexture(renderer, "Res/Textures/Radar.png", "Radar");
	Assets::loadTexture(renderer, "Res/Textures/Sphere.png", "Sphere");
	Assets::loadTexture(renderer, "Res/Textures/Crosshair.png", "Crosshair");
	Assets::loadTexture(renderer, "Res/Textures/RacingCar.png", "RacingCar");
	Assets::loadTexture(renderer, "Res/Textures/Rifle.png", "Rifle");

	Assets::loadMesh("Res/Meshes/Cube.gpmesh", "Mesh_Cube");
	Assets::loadMesh("Res/Meshes/Plane.gpmesh", "Mesh_Plane");
	Assets::loadMesh("Res/Meshes/Sphere.gpmesh", "Mesh_Sphere");
	Assets::loadMesh("Res/Meshes/Rifle.gpmesh", "Mesh_Rifle");
	Assets::loadMesh("Res/Meshes/RacingCar.gpmesh", "Mesh_RacingCar");

	//  load actors
    player = new Player();

	fps = new FPSActor();
	follow = new FollowActor();

	Cube* a = new Cube();
	a->setPosition(Vector3(200.0f, 105.0f, 0.0f));
	a->setScale(100.0f);
	Quaternion q(Vector3::unitY, -Maths::piOver2);
	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::pi + Maths::pi / 4.0f));
	a->setRotation(q);

	Sphere* b = new Sphere();
	b->setPosition(Vector3(200.0f, -75.0f, 0.0f));
	b->setScale(3.0f);

	// Floor and walls

	// Setup floor
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Plane* p = new Plane();
			p->setPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}

	// Left/right walls
	q = Quaternion(Vector3::unitX, Maths::piOver2);
	for (int i = 0; i < 10; i++)
	{
		Plane* p = new Plane();
		p->setPosition(Vector3(start + i * size, start - size, 0.0f));
		p->setRotation(q);

		p = new Plane();
		p->setPosition(Vector3(start + i * size, -start + size, 0.0f));
		p->setRotation(q);
	}

	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
	// Forward/back walls
	for (int i = 0; i < 10; i++)
	{
		Plane* p = new Plane();
		p->setPosition(Vector3(start - size, start + i * size, 0.0f));
		p->setRotation(q);

		p = new Plane();
		p->setPosition(Vector3(-start + size, start + i * size, 0.0f));
		p->setRotation(q);
	}

	// Setup lights
	renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer.getDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// UI elements
	Actor* ui = new Actor();
	ui->setPosition(Vector3(-350.0f, -350.0f, 0.0f));
	SpriteComponent* sc = new SpriteComponent(ui, Assets::getTexture("HealthBar"));

	ui = new Actor();
	ui->setPosition(Vector3(375.0f, -275.0f, 0.0f));
	ui->setScale(0.75f);
	sc = new SpriteComponent(ui, Assets::getTexture("Radar"));

	// Corsshair
	Actor* crosshairActor = new Actor();
	crosshairActor->setScale(2.0f);
	crosshair = new SpriteComponent(crosshairActor, Assets::getTexture("Crosshair"));
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
	inputSystem.close();
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::processInput()
{
	inputSystem.preUpdate();

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

	inputSystem.update();
	const InputState& input = inputSystem.getInputState();

	// Escape: quit game
	if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
	{
		isRunning = false;
	}

	if (input.keyboard.getKeyState(SDL_SCANCODE_1) == ButtonState::Pressed)
	{
		changeCamera(1);
	}
	else if (input.keyboard.getKeyState(SDL_SCANCODE_2) == ButtonState::Pressed)
	{
		changeCamera(2);
	}

	// Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(input);
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

	//  move pending actors to actors
	for (auto pendingActor : pendingActors)
	{
		pendingActor->computeWorldTransform();
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

	//camera->logWorldTransformMatrix();
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

void Game::changeCamera(int mode)
{
	// Disable everything
	fps->setState(Actor::ActorState::Paused);
	fps->setVisible(false);
	crosshair->setVisible(false);
	follow->setState(Actor::ActorState::Paused);
	follow->setVisible(false);

	// Enable the camera specified by the mode
	switch (mode)
	{
	case 1:
	default:
		fps->setState(Actor::ActorState::Active);
		fps->setVisible(true);
		crosshair->setVisible(true);
		break;
	case 2:
		follow->setState(Actor::ActorState::Active);
		follow->setVisible(true);
		break;
	}
}