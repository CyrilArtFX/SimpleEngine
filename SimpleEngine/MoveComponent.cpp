#include "MoveComponent.h"
#include "Maths.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP) : Component(ownerP, updateOrderP)
{
}

void MoveComponent::setForwardSpeed(float forwardSpeedP)
{
	forwardSpeed = forwardSpeedP;
}

void MoveComponent::setStrafeSpeed(float strafeSpeedP)
{
	strafeSpeed = strafeSpeedP;
}

void MoveComponent::setAngularSpeed(float angularSpeedP)
{
	angularSpeed = angularSpeedP;
}

void MoveComponent::update(float dt)
{
	if (!Maths::nearZero(angularSpeed))
	{
		Quaternion newRotation = owner.getRotation();
		float angle = angularSpeed * dt;
		Quaternion increment(Vector3::unitZ, angle);
		newRotation = Quaternion::concatenate(newRotation, increment);
		owner.setRotation(newRotation);
	}

	if (!Maths::nearZero(forwardSpeed) || !Maths::nearZero(strafeSpeed))
	{
		Vector3 newPosition = owner.getPosition();
		newPosition += owner.getForward() * forwardSpeed * dt;
		newPosition += owner.getRight() * strafeSpeed * dt;
		owner.setPosition(newPosition);
	}
}