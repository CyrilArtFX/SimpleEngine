#include "Player.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "InputMoveComponent.h"
#include "Maths.h"

Player::Player() : Actor()
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("car"));
	collision = new CircleCollisionComponent(this);
	collision->setRadius(20.0f);
	InputMoveComponent* mc = new InputMoveComponent(this, collision);
	mc->setMaxForwardSpeed(300.0f);
	mc->setMaxAngularSpeed(Maths::pi);
}