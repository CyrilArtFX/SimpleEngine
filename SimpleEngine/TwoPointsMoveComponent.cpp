#include "TwoPointsMoveComponent.h"
#include "Maths.h"
#include "Actor.h"

TwoPointsMoveComponent::TwoPointsMoveComponent(Actor* ownerP) : MoveComponent(ownerP)
{
}

void TwoPointsMoveComponent::initialize(Vector2 pointAP, Vector2 pointBP)
{
	pointA = pointAP;
	pointB = pointBP;

	owner.setPosition(pointA);
	Vector2 toPoint = pointB - pointA;
	owner.setRotation(Maths::atan2(-toPoint.y, toPoint.x));
}

void TwoPointsMoveComponent::update(float dt)
{
	if (!Maths::nearZero(forwardSpeed))
	{
		Vector2 position = owner.getPosition();
		Vector2 newPosition = position + owner.getForward() * forwardSpeed * dt;
		if (reverse)
		{
			if ((newPosition - position).lengthSq() > (pointA - position).lengthSq())
			{
				newPosition = pointA;
				reverse = false;
				Vector2 toPoint = pointB - position;
				owner.setRotation(Maths::atan2(-toPoint.y, toPoint.x));
			}
		}
		else
		{
			if ((newPosition - position).lengthSq() > (pointB - position).lengthSq())
			{
				newPosition = pointB;
				reverse = true;
				Vector2 toPoint = pointA - position;
				owner.setRotation(Maths::atan2(-toPoint.y, toPoint.x));
			}
		}

		owner.setPosition(newPosition);
	}
}
