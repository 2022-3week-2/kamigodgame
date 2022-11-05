#include "stdafx.h"
#include "Boss.h"

Boss::Boss()
{
}

void Boss::Load()
{
	bossModel.reset(new Model("20Surface"));
}
void Boss::Init()
{
	bossObj = std::move(std::make_unique<Object3D>());
	bossObj->model = bossModel.get();
	bossObj->position = { 0,5,0 };
	bossObj->scale = { 5,5,5 };

	// ÉÇÅ[ÉVÉáÉì
	bossMotion = std::move(std::make_unique<BossRush>());
	bossMotion->SetBossPtr(this);
	bossMotion->Init();
}
void Boss::Update()
{
	if (bossMotion->GetisEnd() == true)
	{

	}
	else
	{
		bossMotion->Update();
	}

	bossObj->UpdateMatrix();
}
void Boss::DrawModel()
{
	bossObj->Draw();
}
