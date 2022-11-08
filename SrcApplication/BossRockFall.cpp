#include "stdafx.h"
#include "BossRockFall.h"
#include "Random.h"

void BossRockFall::Init()
{
	step = Start;
	rocks.clear();
	rockFallTimer = 0;
	rockFallMaxTimer = 120;
	generateTimer = 0;
	generateMaxTimer = 60;
}
void BossRockFall::Update()
{
	// ŠÖ”ƒ|ƒCƒ“ƒ^
	void (BossRockFall:: * pFunc[])() =
	{
		// “o˜^
		&BossRockFall::StartUpdate,
		&BossRockFall::GeneRockUpdate,
		&BossRockFall::RockFallUpdate,
		&BossRockFall::EndUpdate,
	};

	// ŽÀs
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
		step = GeneRock;
	}
}
void BossRockFall::GeneRockUpdate()
{
	Vec3 randomShakeAngle =
	{
		Random::RangeF(-5,5),
		Random::RangeF(-5,5),
		Random::RangeF(-5,5),
	};
	bossPtr->SetRotation(AngleToRadian(randomShakeAngle));

	generateTimer++;
	if (generateTimer >= generateMaxTimer)
	{
		for (int i = 0; i < 10; i++)
		{
			int randomAngle = Random::Range(0, 360);
			int randomLenght = Random::Range(-20, 20);

			//int randomAngle = 0;
			//int randomLenght = i * 10;

			Vec3 randomPos =
			{
				cosf(AngleToRadian(randomAngle)) * randomLenght,
				50.0f,
				sinf(AngleToRadian(randomAngle)) * randomLenght,
			};

			rocks.emplace_back(std::move(std::make_unique<Rock>(
				randomPos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
		}

		bossPtr->SetRotation(AngleToRadian({ 0,0,0 }));
		generateTimer = 0;
		step = RockFall;
	}
}
void BossRockFall::RockFallUpdate()
{
	rockFallTimer++;
	if (rockFallTimer >= rockFallMaxTimer)
	{
		for (const auto& currentRock : rocks)
		{
			currentRock->SetisFall(true);
		}

		rocks.remove_if(
			[](std::unique_ptr<Rock>& rock)
			{
				return !rock->GetisActive();
			});

		rockFallTimer = rockFallMaxTimer;
		if (rocks.size() == 0)
		{
			step = End;
		}
	}

	for (const auto& currentRock : rocks)
	{
		currentRock->Update();
	}
}
void BossRockFall::EndUpdate()
{
	isEnd = true;
}