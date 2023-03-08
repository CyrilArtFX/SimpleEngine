#pragma once
#include <vector>
#include "Vector2.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Quaternion.h"
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
	const Vector3 getPosition() const { return position; }
	const float getScale() const { return scale; }
	const Quaternion getRotation() const { return rotation; }
	Vector3 getForward() const;
	Vector3 getRight() const;
	const Matrix4& getWorldTransform() const { return worldTransform; }

	void setPosition(Vector3 positionP);
	void setScale(float scaleP);
	void setRotation(Quaternion rotationP);
	void setState(ActorState stateP);

	void computeWorldTransform();

	void update(float dt);
	void updateComponents(float dt);
	virtual void updateActor(float dt);
	void addComponent(Component* component);
	void removeComponent(Component* component);

	void processInput(const struct InputState& inputState);
	virtual void actorInput(const struct InputState& inputState);

	void logWorldTransformMatrix();

	/*
	* Transform a point from this actor local space to world space
	*/
	Vector3 transformPoint(Vector3 point);

private:
	Game& game;
	ActorState state{ ActorState::Active };
	Vector3 position{ Vector3::zero };
	float scale{ 1.0f };
	Quaternion rotation{ Quaternion::identity };
	Matrix4 worldTransform;
	bool mustRecomputeWorldTransform{ true };

	vector<Component*> components;
};

