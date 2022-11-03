#pragma once
#include "MoveComponent.h"
#include "Vector2.h"

class TwoPointsMoveComponent : public MoveComponent
{
public:
	TwoPointsMoveComponent(Actor* ownerP);
	TwoPointsMoveComponent() = delete;
	TwoPointsMoveComponent(const TwoPointsMoveComponent&) = delete;
	TwoPointsMoveComponent& operator=(const TwoPointsMoveComponent&) = delete;

	void initialize(Vector2 pointAP, Vector2 pointBP);
	void update(float dt) override;

private:
	Vector2 pointA{ Vector2::zero };
	Vector2 pointB{ Vector2::zero };
	bool reverse{ false };
};

