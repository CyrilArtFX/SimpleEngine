#include "MultiCameraComponent.h"
#include "InputSystem.h"
#include "Actor.h"
#include "CollisionComponent3D.h"

MultiCameraComponent::MultiCameraComponent(class Actor* ownerP, class Actor* targetP) : CameraComponent(ownerP), target(targetP)
{
	targetPos = target->getPosition();
}

void MultiCameraComponent::update(float dt)
{
	if (!target) return;
	targetPos = Vector3::smoothDamp(targetPos, target->getPosition(), targetMoveVelocity, 0.2f, dt);
	Vector3 camPos;
	Vector3 viewTarget;

	if (type == ThirdPerson || type == FirstPerson)
	{
		float yawRadian = Maths::toRadians(yaw);
		Vector3 yawDirection = Vector3{ -Maths::sin(yawRadian), -Maths::cos(yawRadian), 0.0f };

		float pitchRadian = Maths::toRadians(pitch);
		Vector3 pitchDirection = Vector3{ Maths::cos(pitchRadian), 0.0f, -Maths::sin(pitchRadian) };

		Vector3 lookDirection = Vector3{ yawDirection.x * pitchDirection.x, yawDirection.y * pitchDirection.x, pitchDirection.z };

		if (type == ThirdPerson)
		{
			float springArmChecked = springArmLength;
			for (auto iter : collisionsToCheck)
			{
				float t;
				if (iter->intersectWithRay(targetPos, -lookDirection, springArmLength, t))
				{
					springArmChecked = t;

					notify(SPRING_ARM_USED);

					break;
				}
			}
			camPos = targetPos - (lookDirection * springArmChecked);
			viewTarget = targetPos;
		}

		if (type == FirstPerson)
		{
			camPos = target->transformPoint(firstPersonOffset);
			viewTarget = camPos + (lookDirection * 100.0f);
		}
	}

	if (type == Cinematic)
	{
		camPos = cinematicPos;
		viewTarget = targetPos;
	}

	Matrix4 view = Matrix4::createLookAt(camPos, viewTarget, Vector3::unitZ);
	setViewMatrix(view);
}

void MultiCameraComponent::processInput(const InputState& inputState)
{
	if (!target) return;

	if (inputState.keyboard.getKeyState(SDL_SCANCODE_1) == ButtonState::Pressed)
	{
		type = ThirdPerson;
	}
	else if (inputState.keyboard.getKeyState(SDL_SCANCODE_2) == ButtonState::Pressed)
	{
		type = FirstPerson;
	}
	else if (inputState.keyboard.getKeyState(SDL_SCANCODE_3) == ButtonState::Pressed)
	{
		type = Cinematic;

		notify(CINEMATIC_CAMERA);
	}

	if (type == ThirdPerson || type == FirstPerson)
	{
		Vector2 mousePosition = inputState.mouse.getPosition();
		yaw -= mousePosition.x * mouseSensitivity.x;
		pitch = Maths::clamp(pitch + mousePosition.y * mouseSensitivity.y, minPitch, maxPitch);
	}
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

void MultiCameraComponent::setCinematicPos(Vector3 cinematicPosP)
{
	cinematicPos = cinematicPosP;
}

void MultiCameraComponent::setFirstPersonOffset(Vector3 firstPersonOffsetP)
{
	firstPersonOffset = firstPersonOffsetP;
}

void MultiCameraComponent::addCollisionToCheck(CollisionComponent3D* col)
{
	collisionsToCheck.push_back(col);
}
