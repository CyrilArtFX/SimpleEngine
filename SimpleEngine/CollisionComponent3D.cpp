#include "CollisionComponent3D.h"

CollisionComponent3D::CollisionComponent3D(Actor* ownerP) : Component(ownerP)
{
}

bool CollisionComponent3D::intersectWithPoint(Vector3 point)
{
	return false;
}

bool CollisionComponent3D::intersectWithRay(Vector3 rayOrigin, Vector3 rayDirection, float rayLength, float& t)
{
	return false;
}
