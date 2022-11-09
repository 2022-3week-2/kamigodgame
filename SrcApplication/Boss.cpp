#include "stdafx.h"
#include "Boss.h"
#include "BossRush.h"
#include "BossRockFall.h"
#include "Random.h"
#include "Collision.h"

Boss::Boss() :
	collisionRadius(5)
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
	DamageUpdate();
	PlayerHitBoss();


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

void Boss::DamageUpdate()
{
	if (isDamage == false) return;

	static float frame = 0;
	const float maxFrame = 6;
	const float halfFrame = maxFrame / 2;
	const int maxAddScale = 1;
	const Vec3 addScale =
	{
		(maxAddScale / halfFrame),
		(maxAddScale / halfFrame),
		(maxAddScale / halfFrame),
	};

	frame++;
	if (frame <= halfFrame)
	{
		bossObj->scale += addScale;
	}
	else
	{
		bossObj->scale -= addScale;
	}

	if (frame >= maxFrame)
	{
		bossObj->scale = { 5,5,5 };
		frame = 0;
		isDamage = false;
	}
}

void Boss::PlayerHitBoss()
{
	SphereCollider bossCollider =
	{
		bossObj->position,collisionRadius
	};

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
			}
		}
	}
}