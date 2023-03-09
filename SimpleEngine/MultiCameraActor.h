#pragma once
#include "Actor.h"
#include "Subject.h"

class MultiCameraActor : public Actor, public Subject
{
public:
	MultiCameraActor();

	void actorInput(const InputState& inputState) override;
	void updateActor(float dt) override;
	void setCinematicPos(Vector3 cinematicPosP);
	void addCollisionToCheck(class CollisionComponent3D* col);
	void addObserverToThisActor(class IObserver* observer);

private:
	class MoveComponent* moveComponent;
	class MultiCameraComponent* cameraComponent;
	class MeshComponent* meshComponent;

	float farFromHomeDist{ 10000.0f };
};

