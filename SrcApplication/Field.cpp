#include "stdafx.h"
#include "Field.h"

Field::Field()
{
}

void Field::Load()
{
	fieldModel.reset(new Model("Field"));
}
void Field::Init()
{
	fieldObj = std::move(std::make_unique<Object3D>());
	fieldObj->model = fieldModel.get();
	fieldObj->position.y = -2;
	fieldObj->scale = { 30,1,30 };
}
void Field::Update()
{
	fieldObj->UpdateMatrix();
}
void Field::DrawModel()
{
	fieldObj->Draw();
}
