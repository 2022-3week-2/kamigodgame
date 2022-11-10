#include "stdafx.h"
#include "BossShot.h"
#include "Random.h"

void BossShot::Init()
{
	shotCount = 0;
	shotMaxCount = 8;

	shotTimer = 0;
	shotMaxTimer = 15;
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
void BossShot::DrawModel()
{
	for (const auto& current : bullets)
	{
		current->DrawModel();
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
		Vec3 targetVec =
		{
			-targetPoses[shotCount].x,
			0,
			-targetPoses[shotCount].z,
		};

		bullets.emplace_back(
			std::move(std::make_unique<Bullet>(
				bossPtr->GetPosition(),
				targetVec.Norm(),
				60,
				bossPtr->GetBulletModel()
				)));
		bullets.back()->SetScale({ 3,3,3 });

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
	if (bullets.size() == 0)
	{
		isEnd = true;
	}
}