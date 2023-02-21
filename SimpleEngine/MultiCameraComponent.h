#pragma once
#include "CameraComponent.h"
#include "Vector2.h"
#include <vector>

class MultiCameraComponent : public CameraComponent
{
public:
	MultiCameraComponent(class Actor* ownerP, class Actor* targetP);
	MultiCameraComponent() = delete;
	MultiCameraComponent(MultiCameraComponent&) = delete;
	MultiCameraComponent& operator=(MultiCameraComponent&) = delete;

	void update(float dt) override;
	void processInput(const struct InputState& inputState) override;

	void setTarget(class Actor* targetP);
	void setPitchClamp(float minPitchP, float maxPitchP);

	void addCollisionToCheck(class CollisionComponent3D* col);


private:
	class Actor* target;
	float yaw{ -90.0f }; //  "horizontal" rotation
	float pitch{ 30.0f }; //  "vertical" rotation
	float springArmLength{ 500.0f };

	float minPitch{ -35.0f };
	float maxPitch{ 80.0f };

	Vector2 mouseSensitivity{ 0.12f, 0.10f };

	std::vector<class CollisionComponent3D*> collisionsToCheck;

	Vector3 targetPos;
	Vector3 targetMoveVelocity{ Vector3::zero };
};

