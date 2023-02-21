#include "SphereCollisionComponent.h"
#include "Actor.h"
#include <iostream>

SphereCollisionComponent::SphereCollisionComponent(Actor* ownerP) : CollisionComponent3D(ownerP)
{
}

float SphereCollisionComponent::getRadius() const
{
	return radius * owner.getScale();
}

Vector3 SphereCollisionComponent::getCenter() const
{
	return owner.getPosition() + centerOffset;
}

void SphereCollisionComponent::setRadius(float radiusP)
{
	radius = radiusP;
}

void SphereCollisionComponent::setCenterOffset(Vector3 centerOffsetP)
{
	centerOffset = centerOffsetP;
}

bool SphereCollisionComponent::intersectWithPoint(Vector3 point)
{
	Vector3 centerToPoint = point - getCenter();
	return centerToPoint.length() <= getRadius();
}

bool SphereCollisionComponent::intersectWithRay(Vector3 rayOrigin, Vector3 rayDirection, float rayLength, float& t)
{
    float t0, t1; // solutions for t if the ray intersects

    // analytic solution
    Vector3 L = rayOrigin - getCenter();
    float a = Vector3::dot(rayDirection, rayDirection);
    float b = 2 * Vector3::dot(rayDirection, L);
    float c = Vector3::dot(L, L) - getRadius() * getRadius();
    if (!solveQuadratic(a, b, c, t0, t1)) return false;


    if (t0 < 0) {
        t0 = t1; // if t0 is negative, let's use t1 instead
        if (t0 < 0) return false; // both t0 and t1 are negative
    }

    t = t0;
    if (t > rayLength) return false;

    return true;
}

bool SphereCollisionComponent::solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1)
{
    float discr = b * b - 4 * a * c;
    if (discr < 0) return false;
    else if (discr == 0) x0 = x1 = -0.5 * b / a;
    else {
        float q = (b > 0) ?
            -0.5 * (b + sqrt(discr)) :
            -0.5 * (b - sqrt(discr));
        x0 = q / a;
        x1 = c / q;
    }
    if (x0 > x1) std::swap(x0, x1);

    return true;
}
