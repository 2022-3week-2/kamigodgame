#include "stdafx.h"
#include "Field.h"

void Field::StoneInit()
{
	const int stoneNumber = 10;

	for (int i = 0; i < stoneNumber; i++)
	{
		int lenght = 20;
		float radian = AngleToRadian(i * (360 / stoneNumber));

		Vec3 pos =
		{
			cosf(radian) * lenght,
			1.0f,
			sinf(radian) * lenght,
		};

		stones.emplace_back(std::move(std::make_unique<Stone>(pos, stoneModel.get(), i)));
	}
}

void Field::StoneGenerate()
{
}

void Field::StoneUpdate()
{
	for (const auto& current : stones)
	{
		current->Update();
	}
}

void Field::StoneDraw()
{
	for (const auto& current : stones)
	{
		current->DrawModel();
	}
}

Field::Field()
{
}

void Field::Load()
{
	fieldModel.reset(new Model("Field"));
	stoneModel.reset(new Model("sphere"));
}
void Field::Init()
{
	fieldObj = std::move(std::make_unique<Object3D>());
	fieldObj->model = fieldModel.get();
	fieldObj->position.y = -2;
	fieldObj->scale = { 30,1,30 };

	//StoneInit();
}
void Field::Update()
{
	//StoneUpdate();

	fieldObj->UpdateMatrix();
}
void Field::DrawModel()
{
	//StoneDraw();

	fieldObj->Draw();
}
