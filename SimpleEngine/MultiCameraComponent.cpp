#include "MultiCameraComponent.h"
#include "InputSystem.h"
#include "Actor.h"
#include <iostream>

MultiCameraComponent::MultiCameraComponent(class Actor* ownerP, class Actor* targetP) : CameraComponent(ownerP), target(targetP)
{

}

void MultiCameraComponent::update(float dt)
{
	if (!target) return;

	float yawRadian = Maths::toRadians(yaw);
	Vector3 yawDirection = Vector3{ -Maths::sin(yawRadian), -Maths::cos(yawRadian), 0.0f };

	float pitchRadian = Maths::toRadians(pitch);
	Vector3 pitchDirection = Vector3{ Maths::cos(pitchRadian), 0.0f, -Maths::sin(pitchRadian) };

	Vector3 lookDirection = Vector3{ yawDirection.x * pitchDirection.x, yawDirection.y * pitchDirection.x, pitchDirection.z };
	Vector3 camPos = target->getPosition() - (lookDirection * springArmLength);

	Vector3 targetPos = target->getPosition();
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
}

void MultiCameraComponent::setPitchClamp(float minPitchP, float maxPitchP)
{
	minPitch = minPitchP;
	maxPitch = maxPitchP;
}
