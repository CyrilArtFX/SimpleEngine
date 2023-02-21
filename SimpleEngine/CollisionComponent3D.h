#pragma once
#include "Component.h"
#include "Vector3.h"

class CollisionComponent3D : public Component
{
public:
	CollisionComponent3D(Actor* ownerP);
	CollisionComponent3D() = delete;
	CollisionComponent3D(const CollisionComponent3D&) = delete;
	CollisionComponent3D& operator=(const CollisionComponent3D&) = delete;

	virtual bool intersectWithPoint(Vector3 point);
	virtual bool intersectWithRay(Vector3 rayOrigin, Vector3 rayDirection, float rayLength, float& t);
};

