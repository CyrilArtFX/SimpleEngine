#pragma once
#include "Actor.h"
#include "SphereCollisionComponent.h"

class Sphere : public Actor
{
public:
	Sphere();
	
	SphereCollisionComponent* getCollision() const{ return scc; }

private:
	SphereCollisionComponent* scc;
};

