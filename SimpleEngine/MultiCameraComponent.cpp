#include "MultiCameraComponent.h"
#include "InputSystem.h"
#include "Actor.h"
#include "CollisionComponent3D.h"
#include <iostream>

MultiCameraComponent::MultiCameraComponent(class Actor* ownerP, class Actor* targetP) : CameraComponent(ownerP), target(targetP)
{
	targetPos = target->getPosition();
}

void MultiCameraComponent::update(float dt)
{
	if (!target) return;

	float yawRadian = Maths::toRadians(yaw);
	Vector3 yawDirection = Vector3{ -Maths::sin(yawRadian), -Maths::cos(yawRadian), 0.0f };

	float pitchRadian = Maths::toRadians(pitch);
	Vector3 pitchDirection = Vector3{ Maths::cos(pitchRadian), 0.0f, -Maths::sin(pitchRadian) };

	Vector3 lookDirection = Vector3{ yawDirection.x * pitchDirection.x, yawDirection.y * pitchDirection.x, pitchDirection.z };
	targetPos = Vector3::smoothDamp(targetPos, target->getPosition(), targetMoveVelocity, 0.2f, dt);
	float springArmChecked = springArmLength;
	for (auto iter : collisionsToCheck)
	{
		float t;
		if (iter->intersectWithRay(targetPos, -lookDirection, springArmLength, t))
		{
			springArmChecked = t;
			break;
		}
	}
	Vector3 camPos = targetPos - (lookDirection * springArmChecked);

	Matrix4 view = Matrix4::createLookAt(camPos, targetPos, Vector3::unitZ);
	setViewMatrix(view);
}

void MultiCameraComponent::processInput(const InputState& inputState)
{
	if (!target) return;

	Vector2 mousePosition = inputState.mouse.getPosition();
	yaw -= mousePosition.x * mouseSensitivity.x;
	pitch = Maths::clamp(pitch + mousePosition.y * mouseSensitivity.y, minPitch, maxPitch);
}

void MultiCameraComponent::setTarget(Actor* targetP)
{
	target = targetP;
	targetPos = target->getPosition();
}

void MultiCameraComponent::setPitchClamp(float minPitchP, float maxPitchP)
{
	minPitch = minPitchP;
	maxPitch = maxPitchP;
}

void MultiCameraComponent::addCollisionToCheck(CollisionComponent3D* col)
{
	collisionsToCheck.push_back(col);
}
