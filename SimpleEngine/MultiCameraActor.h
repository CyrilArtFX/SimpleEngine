#pragma once
#include "Actor.h"

class MultiCameraActor : public Actor
{
public:
	MultiCameraActor();

	void actorInput(const InputState& inputState) override;

private:
	class MoveComponent* moveComponent;
	class MultiCameraComponent* cameraComponent;
	class MeshComponent* meshComponent;
};

