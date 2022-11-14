#include "stdafx.h"
#include "Beam.h"

Beam::Beam(const Vec3 pos, const Vec3 vec, Model* bulletModel) :
	beamObj(std::move(std::make_unique<Object3D>())),
	isActive(true), activeTimer(0), activeMaxTimer(activeMaxTimer)
{
	beamObj->position = pos;
	beamObj->model = bulletModel;
	beamObj->rotation.y = atan2f(vec.z, -vec.x) - AngleToRadian(90);
	beamObj->scale = { 2.5f,2.5f,1 };
}

void Beam::Update()
{
	const float beamMoveSpeed = 8;
	beamObj->scale.z += beamMoveSpeed;

	const float dis = 30;
	if (beamObj->scale.z >= dis)
	{
		beamObj->scale.x -= 0.25f;
		beamObj->scale.y -= 0.25f;
		if (beamObj->scale.x <= 0)
		{
			isActive = false;
		}
	}

	beamObj->UpdateMatrix();
}

void Beam::DrawModel()
{
	beamObj->Draw();
}
