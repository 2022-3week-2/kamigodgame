#include "stdafx.h"
#include "Boss.h"
#include "BossRush.h"
#include "BossRockFall.h"
#include "Random.h"

Boss::Boss()
{
}

void Boss::Load()
{
	bossModel.reset(new Model("20Surface"));
	rockModel.reset(new Model("sphere"));
	rockShadowModel.reset(new Model("RockShadow"));
}
void Boss::Init()
{
	bossObj = std::move(std::make_unique<Object3D>());
	bossObj->model = bossModel.get();
	bossObj->position = { 0,5,0 };
	bossObj->scale = { 5,5,5 };

	// ÉÇÅ[ÉVÉáÉì
	bossMotion = std::move(std::make_unique<BossRockFall>());
	bossMotion->SetBossPtr(this);
	bossMotion->Init();
}
void Boss::Update()
{
	if (bossMotion->GetisEnd() == true)
	{
		std::unique_ptr<IBossMotion> nextMotion;
		switch (Random::Range(0, 1))
		//switch (1)
		{
		case 0:
			nextMotion = std::make_unique<BossRush>();
			break;

		case 1:
			nextMotion = std::make_unique<BossRockFall>();
			break;

		default:
			break;
		}

		bossMotion = std::move(nextMotion);
		bossMotion->SetBossPtr(this);
		bossMotion->Init();
	}
	else
	{
		bossMotion->Update();
	}

	bossObj->UpdateMatrix();
}
void Boss::DrawModel()
{
	if (bossMotion->GetisEnd() == false)
	{
		bossMotion->DrawModel();
	}

	bossObj->Draw();
}
