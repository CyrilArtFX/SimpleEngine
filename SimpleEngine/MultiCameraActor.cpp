#include "MultiCameraActor.h"
#include "MoveComponent.h"
#include "MultiCameraComponent.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "InputSystem.h"

MultiCameraActor::MultiCameraActor() : Actor()
{
	moveComponent = new MoveComponent(this);
	cameraComponent = new MultiCameraComponent(this, this);
	meshComponent = new MeshComponent(this);
	meshComponent->setMesh(Assets::getMesh("Mesh_RacingCar"));
	setPosition(Vector3{ -800.0f, 0.0f, -100.0f });
}

void MultiCameraActor::actorInput(const InputState& inputState)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	// wasd movement
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_W))
	{
		forwardSpeed += 900.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_S))
	{
		forwardSpeed -= 900.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A))
	{
		angularSpeed -= Maths::pi / 1.7f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D))
	{
		angularSpeed += Maths::pi / 1.7f;
	}

	moveComponent->setForwardSpeed(forwardSpeed);
	moveComponent->setAngularSpeed(angularSpeed);
}

void MultiCameraActor::addCollisionToCheck(CollisionComponent3D* col)
{
	cameraComponent->addCollisionToCheck(col);
}
