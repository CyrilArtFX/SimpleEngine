#pragma once
#include "Actor.h"
#include "CircleCollisionComponent.h"

class Player : public Actor
{
public:
	Player();

private:
	CircleCollisionComponent* collision{ nullptr };
};

