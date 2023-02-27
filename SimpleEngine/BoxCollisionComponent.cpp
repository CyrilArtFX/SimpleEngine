#include "BoxCollisionComponent.h"
#include "Actor.h"
#include "Log.h"
#include "Maths.h"

using Maths::max;
using Maths::min;

BoxCollisionComponent::BoxCollisionComponent(Actor* ownerP) : CollisionComponent3D(ownerP)
{
}

Vector3 BoxCollisionComponent::getCenter() const
{
	return owner.getPosition() + centerOffset;
}

Vector3 BoxCollisionComponent::getHalfExtents() const
{
	return halfExtents * owner.getScale();
}

void BoxCollisionComponent::setCenterOffset(Vector3 centerOffsetP)
{
	centerOffset = centerOffsetP;
}

void BoxCollisionComponent::setHalfExtents(Vector3 halfExtentsP)
{
	if (halfExtentsP.x > 0 && halfExtentsP.y > 0 && halfExtentsP.z > 0)
	{
		halfExtents = halfExtentsP;
	}
	else
	{
		Log::error(LogCategory::Application, "You tried to set a negative half extent.");
	}
}

bool BoxCollisionComponent::intersectWithPoint(Vector3 point)
{
	Vector3 lb = getMinCordCorner();
	Vector3 rt = getMaxCordCorner();

	return point.x >= lb.x && point.x <= rt.x &&
		point.y >= lb.y && point.y <= rt.y &&
		point.z >= lb.z && point.z <= rt.z;
}

bool BoxCollisionComponent::intersectWithRay(Vector3 rayOrigin, Vector3 rayDirection, float rayLength, float& t)
{
	Vector3 lb = getMinCordCorner();
	Vector3 rt = getMaxCordCorner();

	Vector3 dirfrac;
	dirfrac.x = 1.0f / rayDirection.x;
	dirfrac.y = 1.0f / rayDirection.y;
	dirfrac.z = 1.0f / rayDirection.z;

	float t1 = (lb.x - rayOrigin.x) * dirfrac.x;
	float t2 = (rt.x - rayOrigin.x) * dirfrac.x;
	float t3 = (lb.y - rayOrigin.y) * dirfrac.y;
	float t4 = (rt.y - rayOrigin.y) * dirfrac.y;
	float t5 = (lb.z - rayOrigin.z) * dirfrac.z;
	float t6 = (rt.z - rayOrigin.z) * dirfrac.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		t = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		t = tmax;
		return false;
	}

	t = tmin;
	return true;
}

Vector3 BoxCollisionComponent::getMinCordCorner()
{
	return getCenter() - getHalfExtents();
}

Vector3 BoxCollisionComponent::getMaxCordCorner()
{
	return getCenter() + getHalfExtents();
}
