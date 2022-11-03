#pragma once
#include "Actor.h"
#include "CircleCollisionComponent.h"

class Obstacle : public Actor
{
public:
	Obstacle(Vector2 pointAP, Vector2 pointBP);
	~Obstacle();
	
	CircleCollisionComponent& getCollision() const { return *collision; }

private:
	CircleCollisionComponent* collision;
};

