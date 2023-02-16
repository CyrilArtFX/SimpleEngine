#include "Actor.h"
#include <algorithm>
#include "Game.h"
#include "Component.h"
#include "Maths.h"
#include "Log.h"
#include "InputSystem.h"

Actor::Actor() : game(Game::instance())
{
	game.addActor(this);
}

Actor::~Actor()
{
	game.removeActor(this);
	//  remove all components of the actor
	while (!components.empty())
	{
		delete components.back();
	}
}

void Actor::setPosition(Vector3 positionP)
{
	position = positionP;
	mustRecomputeWorldTransform = true;
}

void Actor::setScale(float scaleP)
{
	scale = scaleP;
	mustRecomputeWorldTransform = true;
}

void Actor::setRotation(Quaternion rotationP)
{
	rotation = rotationP;
	mustRecomputeWorldTransform = true;
}

void Actor::setState(ActorState stateP)
{
	state = stateP;
}

void Actor::update(float dt)
{
	if (state == Actor::ActorState::Active)
	{
		computeWorldTransform();
		updateComponents(dt);
		updateActor(dt);
		computeWorldTransform();
	}
}

void Actor::updateComponents(float dt)
{
	for (auto component : components)
	{
		component->update(dt);
	}
}

void Actor::updateActor(float dt)
{
}

void Actor::addComponent(Component* component)
{
	//  we must insert the component in the right place in the vector depending of the component's update order
	int myOrder = component->getUpdateOrder();
	auto iter = begin(components);
	for (; iter != end(components); ++iter)
	{
		if (myOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}

	components.insert(iter, component);
}

void Actor::removeComponent(Component* component)
{
	auto iter = std::find(begin(components), end(components), component);
	if (iter != end(components))
	{
		components.erase(iter);
	}
}

Vector3 Actor::getForward() const
{
	return Vector3::transform(Vector3::unitX, rotation);
}

Vector3 Actor::getRight() const
{
	return Vector3::transform(Vector3::unitY, rotation);
}

void Actor::processInput(const InputState& inputState)
{
	if (state == ActorState::Active) 
	{
		for (auto component : components)
		{
			component->processInput(inputState);
		}
		actorInput(inputState);
	}
}

void Actor::actorInput(const InputState& inputState)
{
}

void Actor::logWorldTransformMatrix()
{
	Log::info("World Transformation Matrix of actor\n" + worldTransform.toString());
}

void Actor::computeWorldTransform()
{
	if (mustRecomputeWorldTransform)
	{
		mustRecomputeWorldTransform = false;
		worldTransform = Matrix4::createScale(scale);
		worldTransform *= Matrix4::createFromQuaternion(rotation);
		worldTransform *= Matrix4::createTranslation(position);


		for (auto component : components)
		{
			component->onUpdateWorldTransform();
		}
	}
}