#include "stdafx.h"
#include "Boss.h"
#include "BossRush.h"
#include "BossRockFall.h"
#include "BossShot.h"
#include "BossRushRockFall.h"
#include "BossRushRockFallWavy.h"
#include "Random.h"
#include "Collision.h"
#include <SpWindow.h>

Boss::Boss() :
	collisionRadius(5), addScaleFrame(0), bossForm(1), maxhp(100), hp(maxhp)
{
}

void Boss::Load()
{
	bossModel.reset(new Model("20Surface"));
	rockModel.reset(new Model("sphere"));
	rockShadowModel.reset(new Model("RockShadow"));
	bulletModel.reset(new Model("sphere"));
	beamModel.reset(new Model("Beam"));
	//beamModel = std::move(std::make_unique<Model>("Beam"));
	wavyModel.reset(new Model("Wavy1"));
}
void Boss::Init()
{
	bossObj = std::move(std::make_unique<Object3D>());
	bossObj->model = bossModel.get();
	bossObj->position = { 0,5,0 };
	bossObj->scale = { 5,5,5 };

	// モーション
	bossMotion = std::move(std::make_unique<BossShot>());
	bossMotion->SetBossPtr(this);
	bossMotion->Init();

	HPGaugeInit();
}
void Boss::Update()
{
	bossCollider =
	{
		bossObj->position,collisionRadius
	};
	PlayerHitBoss();
	BossHitPlayer();

	//bossForm = 3;
	FormUpdate();	// 形態の処理
	MotionUpdate();	// モーションの処理
	DamageUpdate();	// ダメージの処理

	bossObj->UpdateMatrix();

	if (hp <= 0)
	{
		hp = 0;
	}

	HPGaugeUpdate();	// HPゲージの処理
}
void Boss::DrawModel()
{
	if (bossMotion->GetisEnd() == false)
	{
		bossMotion->DrawModel();
	}

	if (isDamage == true)
	{
		*bossObj->brightnessCB.contents = { 1.f, 0, 0, 1.f };
	}
	else
	{
		*bossObj->brightnessCB.contents = { 1.f, 1.f, 1.f, 1.f };
	}

	bossObj->Draw("white");
}
void Boss::DrawFrontSprite()
{
	hpGauge->DrawFrontSprite();
}

void Boss::FormUpdate()
{
	// 形態の処理
	if (hp <= maxhp / 3)
	{
		bossForm = 3;
	}
	else if (hp <= maxhp / 3 * 2)
	{
		bossForm = 2;
	}
	else if (hp <= maxhp)
	{
		bossForm = 1;
	}
}
void Boss::MotionUpdate()
{
	if (bossMotion->GetisEnd() == true)
	{
		std::unique_ptr<IBossMotion> nextMotion;
		switch (Random::Range(0, 2))
		//switch (2)
		{
		case 0:
			if (bossForm == 1)
			{
				nextMotion = std::make_unique<BossRush>();
			}
			if (bossForm == 2)
			{
				nextMotion = std::make_unique<BossRushRockFall>();
			}
			if (bossForm == 3)
			{
				nextMotion = std::make_unique<BossRushRockFallWavy>();
			}
			break;

		case 1:
			nextMotion = std::make_unique<BossRockFall>();
			break;

		case 2:
			nextMotion = std::make_unique<BossShot>();
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
}
void Boss::DamageUpdate()
{
	if (isDamage == false) return;

	const float maxFrame = 6;
	const float halfFrame = maxFrame / 2;
	const int maxAddScale = 1;
	const Vec3 addScale =
	{
		(maxAddScale / halfFrame),
		(maxAddScale / halfFrame),
		(maxAddScale / halfFrame),
	};

	addScaleFrame++;
	if (isScaleMotion == false)
	{
		if (addScaleFrame <= halfFrame)
		{
			bossObj->scale += addScale;
		}
		else
		{
			bossObj->scale -= addScale;
		}
	}

	if (addScaleFrame >= maxFrame)
	{
		if (isScaleMotion == false)
		{
			bossObj->scale = { 5,5,5 };
		}
		addScaleFrame = 0;
		isDamage = false;
	}
}

void Boss::HPGaugeInit()
{
	hpGauge = std::move(std::make_unique<Gauge>(
		// 座標
		Vec3((float)GetSpWindow()->width / 2, (float)GetSpWindow()->height - 100, 0),
		// スケール
		Vec3(4, 4, 0)));
}
void Boss::HPGaugeUpdate()
{
	hpGauge->SetGaugeFrontColor({ 140,25,25 });
	hpGauge->SetGaugeBackColor({ 124,48,48 });
	hpGauge->SetGaugeExrate((float)hp / maxhp);
	hpGauge->Update();
}

void Boss::PlayerHitBoss()
{
	for (std::list<std::unique_ptr<Bullet>>::iterator it = playerPtr->GetBullets()->begin();
		it != playerPtr->GetBullets()->end(); it++)
	{
		const SphereCollider playerBulletCollider =
		{
			it->get()->GetPosition(),it->get()->GetCollisionRadius()
		};

		if (Collision::SphereHitSphere(bossCollider, playerBulletCollider))
		{
			if (it->get()->GetisActive() == true)
			{
				it->get()->SetisActive(false);
				isDamage = true;
				hp -= 0.5f;
			}
		}
	}
}
void Boss::BossHitPlayer()
{
	if (Collision::SphereHitSphere(bossCollider, playerPtr->GetPlayerCollider()))
	{
		playerPtr->SetisDamage(5);
	}
}
