#pragma once
#include "Actor.h"

class MultiCameraActor : public Actor
{
public:
	MultiCameraActor();

	void actorInput(const InputState& inputState) override;
	void setCinematicPos(Vector3 cinematicPosP);
	void addCollisionToCheck(class CollisionComponent3D* col);

private:
	class MoveComponent* moveComponent;
	class MultiCameraComponent* cameraComponent;
	class MeshComponent* meshComponent;
};

