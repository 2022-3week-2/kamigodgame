#include "stdafx.h"
#include "Stone.h"

void Stone::GenerateUpdate()
{
	if (isGenerate == false) return;

	generateEase.Update();
	stoneObj->scale = (Float3)generateEase.Out({ 0,0,0 }, { 1,1,1 });

	if (generateEase.GetisEnd() == true)
	{
		isGenerate = false;
	}
}

Stone::Stone(const Vec3 pos, Model* stoneModel, const int& index) :
	stoneObj(std::move(std::make_unique<Object3D>())),
	isGenerate(true), isCarry(false), collisionRadius(1),
	shotParam({ {0,0,0},0,0 }), isShot(false)
{
	stoneObj->position = pos;
	stoneObj->scale = { 0,0,0 };
	stoneObj->model = stoneModel;
	generatePos = pos;
	this->index = index;

	generateEase.SetEaseTimer(60);
	generateEase.SetPowNum(5);
}

void Stone::Update()
{
	if (isCarry == true) return;

	GenerateUpdate();

	stoneObj->UpdateMatrix();
}

void Stone::ShotUpdate()
{
	if (isShot == false) return;

	stoneObj->position += shotParam.vec * shotParam.speed;
	shotParam.gravity -= 0.05f;
	if (shotParam.gravity <= -1)
	{
		shotParam.gravity = -1;
	}
}

void Stone::DrawModel()
{
	if (isCarry == true) return;

	stoneObj->Draw();
}
