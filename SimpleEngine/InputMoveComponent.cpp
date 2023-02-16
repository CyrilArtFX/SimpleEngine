#include "InputMoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Game.h"
#include <iostream>

InputMoveComponent::InputMoveComponent(Actor* ownerP, CircleCollisionComponent* collisionP) : MoveComponent(ownerP), collision(collisionP)
{
}

void InputMoveComponent::processInput(const InputState& inputState)
{
	float forwardSpeed = 0.0f;
	if (inputState.keyboard.getKeyState(forwardKey) == ButtonState::Held)
	{
		forwardSpeed += maxForwardSpeed;
	}
	if (inputState.keyboard.getKeyState(backKey) == ButtonState::Held)
	{
		forwardSpeed -= maxForwardSpeed;
	}
	setForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (inputState.keyboard.getKeyState(clockwiseKey) == ButtonState::Held)
	{
		angularSpeed -= maxAngularSpeed;
	}
	if (inputState.keyboard.getKeyState(counterClockwiseKey) == ButtonState::Held)
	{
		angularSpeed += maxAngularSpeed;
	}
	setAngularSpeed(angularSpeed);
}


void InputMoveComponent::setMaxForwardSpeed(float maxForwardSpeedP)
{
	maxForwardSpeed = maxForwardSpeedP;
}

void InputMoveComponent::setMaxAngularSpeed(float maxAngularSpeedP)
{
	maxAngularSpeed = maxAngularSpeedP;
}

void InputMoveComponent::setForwardKey(SDL_Scancode key)
{
	forwardKey = key;
}

void InputMoveComponent::setBackKey(SDL_Scancode key)
{
	backKey = key;
}

void InputMoveComponent::setClockwiseKey(SDL_Scancode key)
{
	clockwiseKey = key;
}

void InputMoveComponent::setCounterClockwiseKey(SDL_Scancode key)
{
	counterClockwiseKey = key;
}