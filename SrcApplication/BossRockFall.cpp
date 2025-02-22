#include "stdafx.h"
#include "BossRockFall.h"
#include "Random.h"
#include "Collision.h"

void BossRockFall::Init()
{
	step = Start;
	rocks.clear();
	rockFallTimer = 0;
	rockFallMaxTimer = 60;
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
		&BossRockFall::GeneRockUpdate,
		&BossRockFall::RockFallUpdate,
		&BossRockFall::EndUpdate,
	};

	// 実行
	(this->*pFunc[step])();

	RockHitPlayer();
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
	Vec3 lenght = targetPos - bossPtr->GetBossObj()->position;;
	bossPtr->GetBossObj()->position += vec.Norm() * moveSpeed;

	if (lenght.GetLength() <= 1.f)
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
		//int randomAngle = Random::RangeF(1, 360);
		//int randomAngle = 0;
		//switch (bossPtr->GetBossForm())
		//{
		//case 1:
		//	FourRocksPattern(randomAngle);
		//	break;

		//case 2:
		//	EightRocksPattern(randomAngle);
		//	break;

		//case 3:
		//	SixteenRocksPattern(randomAngle);
		//	break;

		//default:
		//	break;
		//}

		//Pattern();
		Pattern2();
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
void BossRockFall::Pattern()
{
	int generateCount = 0;

	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 6; x++)
		{
			if (generateCount >= 31)
			{
				break;
			}

			const int percent = 75;
			const int space = 10;
			Vec3 pos =
			{
				-25 + (float)x * space,
				50.0f,
				25 - (float)y * space,
			};

			if (y == 0 || y == 5)
			{
				if (x == 0 || x == 1 || x == 4 || x == 5)
				{
					rocks.emplace_back(std::move(std::make_unique<Rock>(
						pos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
					generateCount++;
				}
				else
				{
					if (Random::Bool(percent) == true)
					{
						rocks.emplace_back(std::move(std::make_unique<Rock>(
							pos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
						generateCount++;
					}
				}
			}
			else if (y == 1 || y == 4)
			{
				if (x == 0 || x == 5)
				{
					rocks.emplace_back(std::move(std::make_unique<Rock>(
						pos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
					generateCount++;
				}
				else
				{
					if (Random::Bool(percent) == true)
					{
						rocks.emplace_back(std::move(std::make_unique<Rock>(
							pos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
						generateCount++;
					}
				}
			}
			else
			{
				if (Random::Bool(percent) == true)
				{
					rocks.emplace_back(std::move(std::make_unique<Rock>(
						pos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
					generateCount++;
				}
			}
		}
	}
}
void BossRockFall::Pattern2()
{
	int generateCount = 0;

	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 6; x++)
		{
			if (generateCount >= 27)
			{
				break;
			}

			const int percent = 75;
			const int space = 10;
			Vec3 pos =
			{
				-25 + (float)x * space,
				50.0f,
				25 - (float)y * space,
			};

			if (y == 0 || y == 5)
			{
				if (x == 1 || x == 4)
				{
					rocks.emplace_back(std::move(std::make_unique<Rock>(
						pos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
					generateCount++;
				}
				else if (x == 0 || x == 5)
				{
					continue;
				}
				else
				{
					if (Random::Bool(percent) == true)
					{
						rocks.emplace_back(std::move(std::make_unique<Rock>(
							pos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
						generateCount++;
					}
				}
			}
			else if (y == 1 || y == 4)
			{
				if (x == 0 || x == 5)
				{
					rocks.emplace_back(std::move(std::make_unique<Rock>(
						pos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
					generateCount++;
				}
				else
				{
					if (Random::Bool(percent) == true)
					{
						rocks.emplace_back(std::move(std::make_unique<Rock>(
							pos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
						generateCount++;
					}
				}
			}
			else
			{
				if (Random::Bool(percent) == true)
				{
					rocks.emplace_back(std::move(std::make_unique<Rock>(
						pos, bossPtr->GetRockModel(), bossPtr->GetRockShadowModel())));
					generateCount++;
				}
			}
		}
	}
}

void BossRockFall::RockHitPlayer()
{
	for (const auto& current : rocks)
	{
		SphereCollider rockCollider =
		{
			current->GetPosition(),
			current->GetCollisionRadius()
		};

		if (Collision::SphereHitSphere(rockCollider, bossPtr->GetPlayerPtr()->GetPlayerCollider()))
		{
			bossPtr->GetPlayerPtr()->SetisDamage(10);
		}
	}
}
