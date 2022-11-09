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
		int randomAngle = Random::RangeF(1, 360);
		//int randomAngle = 0;
		switch (bossPtr->GetBossForm())
		{
		case 1:
			FourRocksPattern(randomAngle);
			break;

		case 2:
			EightRocksPattern(randomAngle);
			break;

		case 3:
			SixteenRocksPattern(randomAngle);
			break;

		default:
			break;
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

void BossRockFall::FourRocksPattern(const float& angle)
{
	for (int i = 0; i < 4; i++)
	{
		int lenght = 15;
		float radian = AngleToRadian(angle + i * 90);

		Vec3 pos =
		{
			cosf(radian) * lenght,
			50.0f,
			sinf(radian) * lenght,
		};

		rocks.emplace_back(std::move(std::make_unique<Rock>(
			pos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
	}
}
void BossRockFall::EightRocksPattern(const float& angle)
{
	for (int i = 0; i < 8; i++)
	{
		int lenght = 20;
		float radian = AngleToRadian(angle + i * 45);

		Vec3 pos =
		{
			cosf(radian) * lenght,
			50.0f,
			sinf(radian) * lenght,
		};

		rocks.emplace_back(std::move(std::make_unique<Rock>(
			pos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
	}
}
void BossRockFall::SixteenRocksPattern(const float& angle)
{
	for (int i = 0; i < 16; i++)
	{
		int lenght = i >= 8 ? 22 : 12;
		float radian = AngleToRadian(angle + i * 45);

		Vec3 pos =
		{
			cosf(radian) * lenght,
			50.0f,
			sinf(radian) * lenght,
		};

		rocks.emplace_back(std::move(std::make_unique<Rock>(
			pos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
	}
}
