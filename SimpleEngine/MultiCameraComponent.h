#pragma once
#include "CameraComponent.h"
#include "Vector2.h"
#include "Subject.h"
#include <vector>

enum CameraType
{
	ThirdPerson,
	FirstPerson,
	Cinematic
};

class MultiCameraComponent : public CameraComponent, public Subject
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
	void setCinematicPos(Vector3 cinematicPosP);
	void setFirstPersonOffset(Vector3 firstPersonOffsetP);

	void addCollisionToCheck(class CollisionComponent3D* col);


private:
	class Actor* target;
	float yaw{ -90.0f }; //  "horizontal" rotation
	float pitch{ 30.0f }; //  "vertical" rotation
	float springArmLength{ 500.0f };

	float minPitch{ -35.0f };
	float maxPitch{ 80.0f };

	Vector3 cinematicPos{ Vector3::zero };
	Vector3 firstPersonOffset{ Vector3::zero };

	CameraType type{ ThirdPerson };

	Vector2 mouseSensitivity{ 0.12f, 0.10f };

	std::vector<class CollisionComponent3D*> collisionsToCheck;

	Vector3 targetPos;
	Vector3 targetMoveVelocity{ Vector3::zero };
};

