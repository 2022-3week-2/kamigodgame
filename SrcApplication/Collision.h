#pragma once
#include <SphereCollider.h>
#include <RayCollider.h>

class Collision
{
public:
	static bool SphereHitSphere(const SphereCollider& c1, const SphereCollider& c2);
};

