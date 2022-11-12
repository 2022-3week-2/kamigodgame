#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(const Vec3 pos, const Vec3 vec, const int& activeMaxTimer, Model* bulletModel) :
	bulletObj(std::move(std::make_unique<Object3D>())), speed(1),
	isActive(true), activeTimer(0), activeMaxTimer(activeMaxTimer)
{
	bulletObj->position = pos;
	bulletObj->model = bulletModel;
	this->vec = vec;
}

void Bullet::Update()
{
	bulletObj->position += vec * speed;

	activeTimer++;
	if (activeTimer >= activeMaxTimer)
	{
		activeTimer = activeMaxTimer;
		isActive = false;
	}

	bulletObj->UpdateMatrix();
}

void Bullet::DrawModel()
{
	bulletObj->Draw();
}
