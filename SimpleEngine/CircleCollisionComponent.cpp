#include "CircleCollisionComponent.h"
#include "Actor.h"

CircleCollisionComponent::CircleCollisionComponent(Actor* owner) : Component(owner)
{
}

float CircleCollisionComponent::getRadius() const
{
	return owner.getScale() * radius;
}

void CircleCollisionComponent::setRadius(float radiusP)
{
	radius = radiusP;
}

const Vector2 CircleCollisionComponent::getCenter() const
{
	return owner.getPosition();
}

bool CircleCollisionComponent::intersect(const Vector2 targetPos, const CircleCollisionComponent& targetCol)
{
	Vector2 aCenter = getCenter();
	Vector2 bCenter = targetPos;
	Vector2 ab = bCenter - aCenter;
	float distSq = ab.lengthSq();
	float sumOfRadius = getRadius() + targetCol.getRadius();
	return distSq <= sumOfRadius * sumOfRadius;
}
