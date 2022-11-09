#include "stdafx.h"
#include "BossShot.h"
#include "Random.h"

void BossShot::Init()
{
	shotCount = 0;
	shotMaxCount = 9;

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
	switch (Random::Range(1, 3))
		//switch (1)
	{
	case 1:
		TargetPosPattern1();
		break;
	case 2:
		TargetPosPattern2();
		break;
	case 3:
		TargetPosPattern3();
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

void BossShot::TargetPosPattern1()
{
	const int lenght = 30;
	for (int i = 0; i < shotMaxCount; i++)
	{
		targetPoses.emplace_back(
			cosf(AngleToRadian(i * (360 / shotMaxCount))) * lenght,
			5,
			sinf(AngleToRadian(i * (360 / shotMaxCount))) * lenght);
	}
}
void BossShot::TargetPosPattern2()
{
	const int lenght = 30;
	targetPoses.emplace_back(cosf(AngleToRadian(40)) * lenght, 5, sinf(AngleToRadian(40)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(120)) * lenght, 5, sinf(AngleToRadian(120)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(160)) * lenght, 5, sinf(AngleToRadian(160)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(80)) * lenght, 5, sinf(AngleToRadian(80)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(200)) * lenght, 5, sinf(AngleToRadian(200)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(320)) * lenght, 5, sinf(AngleToRadian(320)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(0)) * lenght, 5, sinf(AngleToRadian(0)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(280)) * lenght, 5, sinf(AngleToRadian(280)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(240)) * lenght, 5, sinf(AngleToRadian(240)) * lenght);
}
void BossShot::TargetPosPattern3()
{
	const int lenght = 30;
	targetPoses.emplace_back(cosf(AngleToRadian(40)) * lenght, 5, sinf(AngleToRadian(40)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(120)) * lenght, 5, sinf(AngleToRadian(120)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(0)) * lenght, 5, sinf(AngleToRadian(0)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(200)) * lenght, 5, sinf(AngleToRadian(200)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(160)) * lenght, 5, sinf(AngleToRadian(160)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(240)) * lenght, 5, sinf(AngleToRadian(240)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(80)) * lenght, 5, sinf(AngleToRadian(80)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(320)) * lenght, 5, sinf(AngleToRadian(320)) * lenght);
	targetPoses.emplace_back(cosf(AngleToRadian(280)) * lenght, 5, sinf(AngleToRadian(280)) * lenght);
}
