#include "Actor.h"
#include <algorithm>
#include "Game.h"
#include "Component.h"
#include "Maths.h"
#include <iostream>

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

void Actor::setPosition(Vector2 positionP)
{
	position = positionP;
	mustRecomputeWorldTransform = true;
}

void Actor::setScale(float scaleP)
{
	scale = scaleP;
	mustRecomputeWorldTransform = true;
}

void Actor::setRotation(float rotationP)
{
	rotation = rotationP;
	mustRecomputeWorldTransform = true;
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

Vector2 Actor::getForward() const
{
	return Vector2(Maths::cos(rotation), Maths::sin(rotation));
}

void Actor::processInput(const Uint8* keyState)
{
	if (state == ActorState::Active) 
	{
		for (auto component : components)
		{
			component->processInput(keyState);
		}
		actorInput(keyState);
	}
}

void Actor::actorInput(const Uint8* keyState)
{
}

void Actor::computeWorldTransform()
{
	if (mustRecomputeWorldTransform)
	{
		Vector2 camPos = game.getRenderer().getCamPos();

		mustRecomputeWorldTransform = false;
		worldTransform = Matrix4::createScale(scale);
		worldTransform *= Matrix4::createRotationZ(rotation);
		worldTransform *= Matrix4::createTranslation(Vector3(position.x - camPos.x, position.y - camPos.y, 0.0f));
		//std::cout << "Player world transform matrix :\n" << worldTransform.toString() << "\n";


		for (auto component : components)
		{
			component->onUpdateWorldTransform();
		}
	}
}