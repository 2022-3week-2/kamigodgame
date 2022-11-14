#include "stdafx.h"
#include "BossShot.h"
#include "Random.h"
#include "Collision.h"

void BossShot::Init()
{
	shotCount = 0;
	shotMaxCount = 8;

	shotTimer = 0;
	shotMaxTimer = 30;
}
void BossShot::Update()
{
	// 関数ポインタ
	void (BossShot:: * pFunc[])() =
	{
		// 登録
		&BossShot::StartUpdate,
		&BossShot::MoveUpdate,
		&BossShot::ShotUpdate,
		&BossShot::EndUpdate,
	};

	// 実行
	(this->*pFunc[step])();

	if (bossPtr->GetBossForm() < 3)
	{
		BulletHitPlayer();

		for (const auto& current : bullets)
		{
			current->Update();
		}

		// 削除
		bullets.remove_if(
			[](std::unique_ptr<Bullet>& bullet)
			{
				return !bullet->GetisActive();
			});
	}
	else
	{
		BeamHitPlayer();

		for (const auto& current : beams)
		{
			current->Update();
		}

		// 削除
		beams.remove_if(
			[](std::unique_ptr<Beam>& beam)
			{
				return !beam->GetisActive();
			});
	}
}
void BossShot::DrawModel()
{
	if (bossPtr->GetBossForm() < 3)
	{
		for (const auto& current : bullets)
		{
			current->DrawModel();
		}
	}
	else
	{
		for (const auto& current : beams)
		{
			current->DrawModel();
		}
	}
}

void BossShot::StartUpdate()
{
	const int index = Random::Range(0, 8);
	const int offset = index * 45;
	const int lenght = 30;
	switch (Random::Range(0, 1))
	{
	case 0:
		for (int i = 0; i < shotMaxCount; i++)
		{
			targetPoses.emplace_back(
				cosf(AngleToRadian(offset + i * 135)) * lenght,
				5,
				sinf(AngleToRadian(offset + i * 135)) * lenght);
		}
		break;
	case 1:
		for (int i = 0; i < shotMaxCount; i++)
		{
			targetPoses.emplace_back(
				cosf(AngleToRadian(offset + i * -135)) * lenght,
				5,
				sinf(AngleToRadian(offset + i * -135)) * lenght);
		}
		break;
	default:
		break;
	}

	step = Move;
}
void BossShot::MoveUpdate()
{
	if (bossPtr->GetPosition().x != targetPoses[shotCount].x ||
		bossPtr->GetPosition().y != targetPoses[shotCount].y ||
		bossPtr->GetPosition().z != targetPoses[shotCount].z)
	{
		bossPtr->SetisScaleMotion(true);
		bossPtr->SetScale(bossPtr->GetScale() - 0.5f);

		if (bossPtr->GetScale().x < 0)
		{
			bossPtr->SetScale({ 0,0,0 });
			bossPtr->SetPosition(targetPoses[shotCount]);
		}
	}
	if (bossPtr->GetPosition().x == targetPoses[shotCount].x &&
		bossPtr->GetPosition().y == targetPoses[shotCount].y &&
		bossPtr->GetPosition().z == targetPoses[shotCount].z)
	{
		bossPtr->SetScale(bossPtr->GetScale() + 0.5f);
		if (bossPtr->GetScale().x > 5)
		{
			bossPtr->SetisScaleMotion(false);
			bossPtr->SetScale({ 5,5,5 });
			step = Shot;
		}
	}
}
void BossShot::ShotUpdate()
{
	shotTimer++;
	if (shotTimer >= shotMaxTimer)
	{
		Vec3 currentPos =
		{
			bossPtr->GetPosition().x,
			3,
			bossPtr->GetPosition().z,
		};

		targetVec =
		{
			-targetPoses[shotCount].x,
			0,
			-targetPoses[shotCount].z,
		};

		if (bossPtr->GetBossForm() < 3)
		{
			bullets.emplace_back(
				std::move(std::make_unique<Bullet>(
					currentPos,
					targetVec.Norm(),
					60,
					bossPtr->GetBulletModel()
					)));
			bullets.back()->SetScale({ 3,3,3 });
			bullets.back()->SetBulletDamage(5);
		}
		else
		{
			beams.emplace_back(
				std::move(std::make_unique<Beam>(
					currentPos,
					targetVec.Norm(),
					bossPtr->GetBeamModel()
					)));
		}

		shotCount++;

		if (shotCount < shotMaxCount)
		{
			step = Move;
			shotTimer = 0;
		}
		else
		{
			step = End;
		}
	}
}
void BossShot::EndUpdate()
{
	if (bossPtr->GetBossForm() < 3)
	{
		if (bullets.size() == 0)
		{
			isEnd = true;
		}
	}
	else
	{
		if (beams.size() == 0)
		{
			isEnd = true;
		}
	}
}

void BossShot::BulletHitPlayer()
{
	for (const auto& current : bullets)
	{
		SphereCollider bulletCollider =
		{
			current->GetPosition(),
			current->GetCollisionRadius()
		};

		if (Collision::SphereHitSphere(bulletCollider, bossPtr->GetPlayerPtr()->GetPlayerCollider()))
		{
			bossPtr->GetPlayerPtr()->SetisDamage(current->GetBulletDamage());
		}
	}
}
void BossShot::BeamHitPlayer()
{
	for (const auto& current : beams)
	{
		Vec2 startPos =
		{
			current->GetPosition().x,
			current->GetPosition().z,
		};

		Vec2 vec =
		{
			targetVec.Norm().x,
			targetVec.Norm().z,
		};

		Vec2 targetPos =
		{
			bossPtr->GetPlayerPtr()->GetPosition().x,
			bossPtr->GetPlayerPtr()->GetPosition().z,
		};

		Vec2 offset =
		{
			-targetVec.z,
			targetVec.x,
		};
		Vec2 startPos1 = startPos + offset.Norm() * +2.5f;
		Vec2 startPos2 = startPos + offset.Norm() * -2.5f;
		Vec2 endPos1 = startPos1 + vec.Norm() * current->GetLenght();
		Vec2 endPos2 = startPos2 + vec.Norm() * current->GetLenght();

		float test1 = (endPos1.x - startPos1.x) * (targetPos.y - startPos1.y) -
			(endPos1.y - startPos1.y) * (targetPos.x - startPos1.x);

		float test2 = (endPos2.x - startPos2.x) * (targetPos.y - startPos2.y) -
			(endPos2.y - startPos2.y) * (targetPos.x - startPos2.x);

		if (test1 <= 0 && test2 >= 0)
		{
			bossPtr->GetPlayerPtr()->SetisDamage(5);
		}
	}
}