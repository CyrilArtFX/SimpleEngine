#pragma once
#include "Actor.h"
#include "Rectangle.h"
#include "RectangleCollisionComponent.h"

class RoadCollider : public Actor
{
public:
	RoadCollider(Rectangle rectP);
	~RoadCollider();

	RectangleCollisionComponent& getCollision() const { return *collision; }

private:
	Rectangle rect{ Rectangle::nullRect };
	RectangleCollisionComponent* collision{ nullptr };
};

