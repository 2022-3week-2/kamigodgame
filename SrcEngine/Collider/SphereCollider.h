#pragma once
#include "ICollider.h"
#include "SpMath.h"
class SphereCollider :
	public ICollider
{
public:
	SphereCollider() :pos({ 0,0,0 }), r(0) {};
	SphereCollider(Float3 pos, float r) :pos(pos), r(r) {};

public:
	Float3 pos;
	float r;
};

