#include "Obstacle.h"
#include "SpriteComponent.h"
#include "TwoPointsMoveComponent.h"
#include "Assets.h"
#include "Game.h"

Obstacle::Obstacle(Vector2 pointAP, Vector2 pointBP) : Actor()
{
	setScale(1.0f);
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("obstacle"));
	TwoPointsMoveComponent* mc = new TwoPointsMoveComponent(this);
	mc->setForwardSpeed(200.0f);
	mc->initialize(pointAP, pointBP);
	collision = new CircleCollisionComponent(this);
	collision->setRadius(32.0f);

	getGame().addObstacle(this);
}

Obstacle::~Obstacle()
{
	getGame().removeObstacle(this);
}
