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

	void processInput(const Uint8* keyState);

	void setMaxForwardSpeed(float maxForwardSpeedP);
	void setMaxAngularSpeed(float maxAngularSpeedP);

	void setForwardKey(int key);
	void setBackKey(int key);
	void setClockwiseKey(int key);
	void setCounterClockwiseKey(int key);

	void update(float dt) override;

private:
	float maxForwardSpeed{ 0.0f };
	float maxAngularSpeed{ 0.0f };

	int forwardKey{ SDL_SCANCODE_W };
	int backKey{ SDL_SCANCODE_S };
	int clockwiseKey{ SDL_SCANCODE_D };
	int counterClockwiseKey{ SDL_SCANCODE_A };

	void testForObstacles(Vector2 newPosition);
	CircleCollisionComponent* collision{ nullptr };
};
