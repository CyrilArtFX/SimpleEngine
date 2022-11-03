#include "RoadCollider.h"
#include "RectangleCollisionComponent.h"
#include "Game.h"

RoadCollider::RoadCollider(Rectangle rectP) : Actor(), rect(rectP)
{
	collision = new RectangleCollisionComponent(this);
	collision->setRectangle(rect);

	getGame().addRoadCollider(this);
}

RoadCollider::~RoadCollider()
{
	getGame().removeRoadCollider(this);
}