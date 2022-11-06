#include "stdafx.h"
#include "Rock.h"

Rock::Rock(const Vec3 pos, Model* rockModel) :
	rockObj(std::move(std::make_unique<Object3D>())),
	gravity(0), isActive(true)
{
	rockObj->position = pos;
	rockObj->model = rockModel;
}

void Rock::Update()
{
	rockObj->position.y -= gravity;
	gravity += 0.05;
	if (gravity >= 1)
	{
		gravity = 1;
	}

	if (rockObj->position.y <= 0)
	{
		isActive = false;
	}

	rockObj->UpdateMatrix();
}

void Rock::DrawModel()
{
	rockObj->Draw();
}
