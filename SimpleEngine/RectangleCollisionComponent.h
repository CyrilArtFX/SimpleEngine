#pragma once
#include "Component.h"
#include "Rectangle.h"
#include "Vector2.h"

class RectangleCollisionComponent : public Component
{
public:
	RectangleCollisionComponent(Actor* owner);
	RectangleCollisionComponent() = delete;
	RectangleCollisionComponent(const RectangleCollisionComponent&) = delete;
	RectangleCollisionComponent& operator=(const RectangleCollisionComponent&) = delete;

	Rectangle getRectangle() const { return rectangle; }
	void setRectangle(Rectangle rectangleP);

	bool intersect(const Vector2 targetPos);

private:
	Rectangle rectangle{ Rectangle::nullRect };
};