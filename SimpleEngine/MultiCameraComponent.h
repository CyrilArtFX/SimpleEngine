#pragma once
#include "CameraComponent.h"
#include "Vector2.h"

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


private:
	class Actor* target;
	float yaw{ 0.0f }; //  "horizontal" rotation
	float pitch{ 0.0f }; //  "vertical" rotation
	float springArmLength{ 500.0f };

	float minPitch{ -60.0f };
	float maxPitch{ 80.0f };

	Vector2 mouseSensitivity{ 0.12f, 0.10f };
};

