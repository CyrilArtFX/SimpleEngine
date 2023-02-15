#pragma once
#include <vector>
#include "Vector2.h"
#include "Matrix4.h"
#include "SDL_stdinc.h"
using std::vector;

class Game;
class Component;

class Actor
{
public:
	enum class ActorState
	{
		Active,
		Paused,
		Dead
	};

	Actor();
	virtual ~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	Game& getGame() const { return game; }
	const ActorState getState() const { return state; }
	const Vector2 getPosition() const { return position; }
	const float getScale() const { return scale; }
	const float getRotation() const { return rotation; }
	Vector2 getForward() const;
	const Matrix4& getWorldTransform() const { return worldTransform; }

	void setPosition(Vector2 positionP);
	void setScale(float scaleP);
	void setRotation(float rotationP);
	void computeWorldTransform();

	void update(float dt);
	void updateComponents(float dt);
	virtual void updateActor(float dt);
	void addComponent(Component* component);
	void removeComponent(Component* component);

	void processInput(const Uint8* keyState);
	virtual void actorInput(const Uint8* keyState);

private:
	Game& game;
	ActorState state{ ActorState::Active };
	Vector2 position{ Vector2::zero };
	float scale{ 1.0f };
	float rotation{ 0.0f }; //  in radians
	Matrix4 worldTransform;
	bool mustRecomputeWorldTransform{ true };

	vector<Component*> components;
};

