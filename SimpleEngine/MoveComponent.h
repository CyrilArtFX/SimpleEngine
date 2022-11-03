#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	MoveComponent(Actor* ownerP, int updateOrder = 10);
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator=(const MoveComponent&) = delete;

	float getForwardSpeed() const { return forwardSpeed; }
	void setForwardSpeed(float forwardSpeedP);
	float getAngularSpeed() const { return angularSpeed; }
	void setAngularSpeed(float angularSpeedP);

	void update(float dt) override;

protected:
	float forwardSpeed{ 0.0f };
	float angularSpeed{ 0.0f };
};