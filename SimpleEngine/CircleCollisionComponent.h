#pragma once
#include "Component.h"
#include "Vector2.h"

class CircleCollisionComponent : public Component
{
public:
	CircleCollisionComponent(Actor* owner);
	CircleCollisionComponent() = delete;
	CircleCollisionComponent(const CircleCollisionComponent&) = delete;
	CircleCollisionComponent& operator=(const CircleCollisionComponent&) = delete;

	float getRadius() const;
	void setRadius(float radiusP);

	const Vector2 getCenter() const;

	bool intersect(const Vector2 targetPos, const CircleCollisionComponent& targetCol);

private:
	float radius{ 1.0f };
};