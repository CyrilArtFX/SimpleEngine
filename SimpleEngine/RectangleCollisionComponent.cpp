#include "RectangleCollisionComponent.h"
#include "Actor.h"

RectangleCollisionComponent::RectangleCollisionComponent(Actor* owner) : Component(owner)
{
}

void RectangleCollisionComponent::setRectangle(Rectangle rectangleP)
{
	rectangle = rectangleP;
}

bool RectangleCollisionComponent::intersect(const Vector2 targetPos)
{
	Vector2 pos = owner.getPosition();
	float scale = owner.getScale();
	return targetPos.x >= pos.x * scale + rectangle.x && targetPos.x <= pos.x + (rectangle.x + rectangle.width) * scale
		&& targetPos.y >= pos.y * scale + rectangle.y && targetPos.y <= pos.y + (rectangle.y + rectangle.height) * scale;
}
