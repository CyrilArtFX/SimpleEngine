#include "Sphere.h"
#include "MeshComponent.h"
#include "Assets.h"

Sphere::Sphere() : Actor()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));

	scc = new SphereCollisionComponent(this);
	scc->setRadius(15.0f);
}
