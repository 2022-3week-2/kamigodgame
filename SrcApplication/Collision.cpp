#include "stdafx.h"
#include "Collision.h"

bool Collision::SphereHitSphere(const SphereCollider& c1, const SphereCollider& c2)
{
	return
	{
		(c2.pos.x - c1.pos.x) * (c2.pos.x - c1.pos.x) +
		(c2.pos.y - c1.pos.y) * (c2.pos.y - c1.pos.y) +
		(c2.pos.z - c1.pos.z) * (c2.pos.z - c1.pos.z) <=
		(c2.r + c1.r) * (c2.r + c1.r)
	};
}
