#pragma once
#include "CollisionComponent3D.h"

class BoxCollisionComponent : public CollisionComponent3D
{
public:
	BoxCollisionComponent(Actor* ownerP);
	BoxCollisionComponent() = delete;
	BoxCollisionComponent(const BoxCollisionComponent&) = delete;
	BoxCollisionComponent& operator=(const BoxCollisionComponent&) = delete;

	Vector3 getCenter() const;
	Vector3 getHalfExtents() const;

	void setCenterOffset(Vector3 centerOffsetP);
	void setHalfExtents(Vector3 halfExtentsP);

	bool intersectWithPoint(Vector3 point) override;
	bool intersectWithRay(Vector3 rayOrigin, Vector3 rayDirection, float rayLength, float& t) override;

private:
	Vector3 centerOffset{ Vector3::zero };
	Vector3 halfExtents{ 5.0f, 5.0f, 5.0f };

	Vector3 getMinCordCorner();
	Vector3 getMaxCordCorner();
};

