#pragma once
#include "Actor.h"
#include "BoxCollisionComponent.h"

class Cube : public Actor
{
public:
	Cube();

	BoxCollisionComponent* getCollision() { return bcc; }

private:
	BoxCollisionComponent* bcc;
};

