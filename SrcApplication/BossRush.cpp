#include "stdafx.h"
#include "BossRush.h"

void BossRush::Init()
{
	step = Start;
	moveSpeed = 2;
	rushSpeed = 1;

	stayRushTimer = 0;		// ラッシュする前のクールタイム
	stayRushMaxTimer = 60;	// マックスクールタイム

	StartInit();
}
void BossRush::Update()
{
	// 関数ポインタ
	void (BossRush:: * pFunc[])() =
	{
		// 登録
		&BossRush::StartUpdate,
		&BossRush::Rush1Update,
		&BossRush::Rush2Update,
		&BossRush::EndUpdate,
	};

	// 実行
	(this->*pFunc[step])();
}
void BossRush::DrawModel()
{
}

void BossRush::StartInit()
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
	noneBezierOut.AddPoint({ 0,5,30 });
}
void BossRush::StartUpdate()
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
		step = Rush1;
	}
}
void BossRush::Rush1Update()
{
	stayRushTimer++;
	if (stayRushTimer >= stayRushMaxTimer)
	{
		stayRushTimer = stayRushMaxTimer;

		const Vec3 targetPos = { 0,5,-40 };
		Vec3 vec = targetPos - bossPtr->GetBossObj()->position;
		bossPtr->GetBossObj()->position += vec.Norm() * rushSpeed;

		if (vec.GetLength() <= 0.5f)
		{
			bossPtr->GetBossObj()->position = { 50,5,0 };
			stayRushTimer = 0;
			step = Rush2;
		}
	}
}
void BossRush::Rush2Update()
{
	stayRushTimer++;
	if (stayRushTimer >= stayRushMaxTimer)
	{
		stayRushTimer = stayRushMaxTimer;

		const Vec3 targetPos = { -30,5,0 };
		Vec3 vec = targetPos - bossPtr->GetBossObj()->position;
		bossPtr->GetBossObj()->position += vec.Norm() * rushSpeed;

		if (vec.GetLength() <= 0.5f)
		{
			bossPtr->GetBossObj()->position = targetPos;
			stayRushTimer = 0;
			step = End;
		}
	}
}
void BossRush::EndUpdate()
{
	isEnd = true;
}