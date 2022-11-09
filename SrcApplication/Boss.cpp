#include "stdafx.h"
#include "Boss.h"
#include "BossRush.h"
#include "BossRockFall.h"
#include "BossShot.h"
#include "Random.h"
#include "Collision.h"

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

	gaugeSprite.reset(new Sprite("Resources/Sprite/BossSprite/bossGaugeFrame.png", "GeugeSprite"));
	gaugeFrontColorSprite.reset(new Sprite("white"));
	gaugeBackColorSprite.reset(new Sprite("white"));
}
void Boss::Init()
{
	bossObj = std::move(std::make_unique<Object3D>());
	bossObj->model = bossModel.get();
	bossObj->position = { 0,5,0 };
	bossObj->scale = { 5,5,5 };

	// モーション
	bossMotion = std::move(std::make_unique<BossRockFall>());
	bossMotion->SetBossPtr(this);
	bossMotion->Init();

	HPGaugeInit();
}
void Boss::Update()
{
	PlayerHitBoss();

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
void Boss::DrawSpriteFront()
{
	gaugeSprite->Draw();
	gaugeBackColorSprite->Draw();
	gaugeFrontColorSprite->Draw();
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
			//switch (1)
		{
		case 0:
			nextMotion = std::make_unique<BossRush>();
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
	// フレーム
	gaugeSprite->position = { 1280 / 2,600,0 };
	gaugeSprite->scale = { 4,4,0 };

	// 前の色
	float xAxisMaxScale = 126 * gaugeSprite->scale.x;
	float hpExrate = (float)hp / maxhp;
	gaugeFrontColorSprite->scale = Vec3(126 * hpExrate, 6, 0) * (Vec3)gaugeSprite->scale;
	gaugeFrontColorSprite->position =
	{
		gaugeSprite->position.x - (xAxisMaxScale - gaugeFrontColorSprite->scale.x) / 2,
		gaugeSprite->position.y,
		gaugeSprite->position.z
	};
	gaugeFrontColorSprite->brightness = { 0.55f,0.1f,0.1f,1.f };

	// 後ろの色
	gaugeBackColorSprite->scale = gaugeFrontColorSprite->scale;
	gaugeBackColorSprite->position = gaugeFrontColorSprite->position;
	gaugeBackColorSprite->brightness = { 0.49f,0.19f,0.19f,1.f };
}
void Boss::HPGaugeUpdate()
{
	// 前の色の処理
	float xAxisMaxScale = 126 * gaugeSprite->scale.x;
	float hpExrate = (float)hp / maxhp;
	gaugeFrontColorSprite->scale = Vec3(126 * hpExrate, 6, 0) * (Vec3)gaugeSprite->scale;
	gaugeFrontColorSprite->position =
	{
		gaugeSprite->position.x - (xAxisMaxScale - gaugeFrontColorSprite->scale.x) / 2,
		gaugeSprite->position.y,
		gaugeSprite->position.z
	};

	// 後ろの色の処理
	if (gaugeBackColorSprite->scale.x >= gaugeFrontColorSprite->scale.x)
	{
		const float subParam = 0.5f;
		gaugeBackColorSprite->scale.x -= subParam;
		gaugeBackColorSprite->position.x -= subParam / 2;
	}
	if (gaugeBackColorSprite->scale.x <= gaugeFrontColorSprite->scale.x)
	{
		gaugeBackColorSprite->scale.x = gaugeFrontColorSprite->scale.x;
		gaugeBackColorSprite->position.x = gaugeFrontColorSprite->position.x;
	}

	gaugeSprite->UpdateMatrix();
	gaugeFrontColorSprite->UpdateMatrix();
	gaugeBackColorSprite->UpdateMatrix();
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
				hp--;
			}
		}
	}
}