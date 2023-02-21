#pragma once
#include "CollisionComponent3D.h"

class SphereCollisionComponent : public CollisionComponent3D
{
public:
	SphereCollisionComponent(Actor* ownerP);
	SphereCollisionComponent() = delete;
	SphereCollisionComponent(const SphereCollisionComponent&) = delete;
	SphereCollisionComponent& operator=(const SphereCollisionComponent&) = delete;

	float getRadius() const;
	Vector3 getCenter() const;

	void setRadius(float radiusP);
	void setCenterOffset(Vector3 centerOffsetP);

	bool intersectWithPoint(Vector3 point) override;
	bool intersectWithRay(Vector3 rayOrigin, Vector3 rayDirection, float rayLength, float& t) override;

private:
	float radius{ 10.0f };
	Vector3 centerOffset{ Vector3::zero };

	bool solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1);
};

