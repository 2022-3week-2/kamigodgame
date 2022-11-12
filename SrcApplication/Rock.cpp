#include "stdafx.h"
#include "Rock.h"

Rock::Rock(const Vec3 pos, Model* rockModel, Model* rockShadowModel) :
	rockObj(std::move(std::make_unique<Object3D>())),
	rockShadowObj(std::move(std::make_unique<Object3D>())),
	gravity(0), isActive(true), isFall(false)
{
	rockObj->position = pos;
	rockObj->scale = { 5,5,5 };
	rockObj->model = rockModel;

	rockShadowObj->position = { pos.x,0,pos.z };
	rockShadowObj->scale = { 5,1,5 };
	rockShadowObj->model = rockShadowModel;

	collisionRadius = 5;
}

void Rock::Update()
{
	if (isFall == true)
	{
		rockObj->position.y -= gravity;
		gravity += 0.05f;
		if (gravity >= 0.75f)
		{
			gravity = 0.75f;
		}

		if (rockObj->position.y <= 0)
		{
			isActive = false;
		}
	}

	rockObj->UpdateMatrix();
	rockShadowObj->UpdateMatrix();
}

void Rock::DrawModel()
{
	rockShadowObj->Draw();
	rockObj->Draw();
}
