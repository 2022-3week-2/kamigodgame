#include "stdafx.h"
#include "BossRockFall.h"
#include "Random.h"

void BossRockFall::Init()
{
	step = Start;
	rocks.clear();
	rockFallTimer = 0;
	rockFallMaxTimer = 540;
	generateTimer = 0;
	generateMaxTimer = 30;
}
void BossRockFall::Update()
{
	// 関数ポインタ
	void (BossRockFall:: * pFunc[])() =
	{
		// 登録
		&BossRockFall::StartUpdate,
		&BossRockFall::RockFallUpdate,
		&BossRockFall::EndUpdate,
	};

	// 実行
	(this->*pFunc[step])();
}
void BossRockFall::DrawModel()
{
	for (const auto& currentRock : rocks)
	{
		currentRock->DrawModel();
	}
}

void BossRockFall::StartUpdate()
{
	const float moveSpeed = 0.5f;
	const Vec3 targetPos = { 0,5,0 };
	Vec3 vec = targetPos - bossPtr->GetBossObj()->position;
	bossPtr->GetBossObj()->position += vec.Norm() * moveSpeed;

	if (vec.GetLength() <= 0.5f)
	{
		bossPtr->GetBossObj()->position = { 0,5,0 };
		step = RockFall;
	}
}
void BossRockFall::RockFallUpdate()
{
	rockFallTimer++;
	if (rockFallTimer < rockFallMaxTimer)
	{
		generateTimer++;
		if (generateTimer >= generateMaxTimer)
		{
			int randomAngle = Random::Range(0, 360);
			int randomLenght = Random::Range(-30, 30);

			Vec3 randomPos =
			{
				cosf(AngleToRadian(randomAngle)) * randomLenght,
				50.0f,
				sinf(AngleToRadian(randomAngle)) * randomLenght,
			};

			rocks.emplace_back(std::move(std::make_unique<Rock>(
				randomPos, bossPtr->GetRockModel())));

			generateTimer = 0;
		}
	}

	for (const auto& currentRock : rocks)
	{
		currentRock->Update();
	}

	rocks.remove_if(
		[](std::unique_ptr<Rock>& rock)
		{
			return !rock->GetisActive();
		});

	if (rockFallTimer >= rockFallMaxTimer)
	{
		rockFallTimer = rockFallMaxTimer;
		if (rocks.size() == 0)
		{
			step = End;
		}
	}
}
void BossRockFall::EndUpdate()
{
	isEnd = true;
}