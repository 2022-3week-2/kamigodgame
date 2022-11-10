#include "stdafx.h"
#include "BossRushRockFall.h"

void BossRushRockFall::Init()
{
	step = Start;
	moveSpeed = 2;
	rushSpeed = 1;

	stayRushTimer = 0;		// ラッシュする前のクールタイム
	stayRushMaxTimer = 60;	// マックスクールタイム

	angleVec = bossPtr->GetPlayerPtr()->GetPosition() - Vec3(0, 0, 0);

	Vec3 targetPos = angleVec.Norm() * 30;
	targetPos.y = 5;

	BezierInit(targetPos);
}
void BossRushRockFall::Update()
{
	// 関数ポインタ
	void (BossRushRockFall:: * pFunc[])() =
	{
		// 登録
		&BossRushRockFall::StartUpdate,
		&BossRushRockFall::Rush1Update,
		&BossRushRockFall::MoveUpdate,
		&BossRushRockFall::Rush2Update,
		&BossRushRockFall::EndUpdate,
	};

	RockFallUpdate();

	// 実行
	(this->*pFunc[step])();
}
void BossRushRockFall::DrawModel()
{
	for (const auto& currentRock : rocks)
	{
		currentRock->DrawModel();
	}
}

void BossRushRockFall::BezierInit(const Vec3& endPos)
{
	const int halfTimer = 60;
	const int powNum = 3;
	noneBezierIn.SetEaseTime(halfTimer);
	noneBezierIn.SetEasePowNum(powNum);
	noneBezierIn.ReSet();
	noneBezierOut.SetEaseTime(halfTimer);
	noneBezierOut.SetEasePowNum(powNum);
	noneBezierOut.ReSet();

	// 中間地点
	Vec3 centerPos =
	{
		bossPtr->GetBossObj()->position.x / 2,
		30,
		fabsf(bossPtr->GetBossObj()->position.x - 30) / 2
	};

	noneBezierIn.AddPoint(bossPtr->GetBossObj()->position);
	noneBezierIn.AddPoint(centerPos / 2);
	noneBezierIn.AddPoint(centerPos);

	noneBezierOut.AddPoint(centerPos);
	noneBezierOut.AddPoint(centerPos / 2 + centerPos);
	noneBezierOut.AddPoint(endPos);
	this->endPos = endPos;
}
void BossRushRockFall::StartUpdate()
{
	if (noneBezierIn.GetisEnd() == false)
	{
		noneBezierIn.Update();
		bossPtr->GetBossObj()->position =
			noneBezierIn.InterPolation(BezierCurve::EaseIn);
	}
	else
	{
		noneBezierOut.Update();
		bossPtr->GetBossObj()->position =
			noneBezierOut.InterPolation(BezierCurve::EaseOut);
	}

	if (noneBezierOut.GetisEnd() == true)
	{
		noneBezierIn.ReSet();
		noneBezierOut.ReSet();
		noneBezierIn.ClearPoints();
		noneBezierOut.ClearPoints();
		step = Rush1;
	}
}
void BossRushRockFall::Rush1Update()
{
	stayRushTimer++;
	if (stayRushTimer >= stayRushMaxTimer)
	{
		stayRushTimer = stayRushMaxTimer;

		//const Vec3 targetPos = { endPos.x,5,-30 };
		const Vec3 targetPos = { -endPos.x,5,-endPos.z };
		Vec3 vec = targetPos - bossPtr->GetBossObj()->position;
		//Vec3 vec = { targetPos.x,0,-targetPos.z };
		Vec3 lenght = targetPos - bossPtr->GetBossObj()->position;
		bossPtr->GetBossObj()->position += vec.Norm() * rushSpeed;

		if (lenght.GetLength() <= 0.5f)
		{
			BezierInit({ endPos.Cross({ 0,1,0 }).x,5,endPos.Cross({ 0,1,0 }).z });
			stayRushTimer = 0;
			GeneRockUpdate();
			step = Move;
		}
	}
}
void BossRushRockFall::MoveUpdate()
{
	rockFallTimer++;

	if (noneBezierIn.GetisEnd() == false)
	{
		noneBezierIn.Update();
		bossPtr->GetBossObj()->position =
			noneBezierIn.InterPolation(BezierCurve::EaseIn);
	}
	else
	{
		noneBezierOut.Update();
		bossPtr->GetBossObj()->position =
			noneBezierOut.InterPolation(BezierCurve::EaseOut);
	}

	if (noneBezierOut.GetisEnd() == true)
	{
		noneBezierIn.ReSet();
		noneBezierOut.ReSet();
		noneBezierIn.ClearPoints();
		noneBezierOut.ClearPoints();
		step = Rush2;
	}
}
void BossRushRockFall::Rush2Update()
{
	stayRushTimer++;
	if (stayRushTimer >= stayRushMaxTimer)
	{
		stayRushTimer = stayRushMaxTimer;

		const Vec3 targetPos = { -endPos.x,5,-endPos.z };
		Vec3 vec = targetPos - bossPtr->GetBossObj()->position;
		//Vec3 vec = { targetPos.x,0,-targetPos.z };
		Vec3 lenght = vec;
		bossPtr->GetBossObj()->position += vec.Norm() * rushSpeed;

		if (lenght.GetLength() <= 0.5f)
		{
			bossPtr->GetBossObj()->position = targetPos;
			stayRushTimer = 0;
			step = End;
		}
	}
}
void BossRushRockFall::EndUpdate()
{
	isEnd = true;
}

void BossRushRockFall::GeneRockUpdate()
{
	for (int i = 0; i < 4; i++)
	{
		int angle = 45;
		int lenght = 20;
		float offsetRadian = atan2f(endPos.z, endPos.x);
		float radian = AngleToRadian(angle + i * 90) + offsetRadian;

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
void BossRushRockFall::RockFallUpdate()
{
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
	}

	for (const auto& currentRock : rocks)
	{
		currentRock->Update();
	}
}
