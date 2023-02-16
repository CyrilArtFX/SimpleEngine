#pragma once
#include "MoveComponent.h"
#include "CircleCollisionComponent.h"
#include "Vector2.h"
#include <SDL_stdinc.h>
#include <SDL_scancode.h>

class InputMoveComponent : public MoveComponent
{
public:
	InputMoveComponent(Actor* ownerP, CircleCollisionComponent* collisionP);
	InputMoveComponent() = delete;
	InputMoveComponent(const InputMoveComponent&) = delete;
	InputMoveComponent& operator=(const InputMoveComponent&) = delete;

	void processInput(const struct InputState& inputState);

	void setMaxForwardSpeed(float maxForwardSpeedP);
	void setMaxAngularSpeed(float maxAngularSpeedP);

	void setForwardKey(SDL_Scancode key);
	void setBackKey(SDL_Scancode key);
	void setClockwiseKey(SDL_Scancode key);
	void setCounterClockwiseKey(SDL_Scancode key);

private:
	float maxForwardSpeed{ 0.0f };
	float maxAngularSpeed{ 0.0f };

	SDL_Scancode forwardKey{ SDL_SCANCODE_W };
	SDL_Scancode backKey{ SDL_SCANCODE_S };
	SDL_Scancode clockwiseKey{ SDL_SCANCODE_D };
	SDL_Scancode counterClockwiseKey{ SDL_SCANCODE_A };

	CircleCollisionComponent* collision{ nullptr };
};
