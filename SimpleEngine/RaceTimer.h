#pragma once
#include "Actor.h"
#include "RectangleCollisionComponent.h"

class RaceTimer : public Actor
{
public:
	RaceTimer();

	void updateActor(float dt) override;

private:
	RectangleCollisionComponent* checkpoint1{ nullptr };
	RectangleCollisionComponent* checkpoint2{ nullptr };
	RectangleCollisionComponent* checkpoint3{ nullptr };
	int checkpointPassed{ 0 };
	float timer{ 0 };
};

