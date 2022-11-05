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
	switch (step)
	{
	case Start:
		StartUpdate();
		break;
	case Rush1:
		Rush1Update();
		break;
	case Rush2:
		Rush2Update();
		break;
	case End:
		EndUpdate();
		break;

	default:
		break;
	}
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
		bossPtr->bossObj->position.x / 2,
		30,
		fabsf(bossPtr->bossObj->position.x - 30) / 2
	};

	noneBezierIn.AddPoint(bossPtr->bossObj->position);
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
		bossPtr->bossObj->position =
			noneBezierIn.InterPolation(BezierCurve::EaseIn);
	}
	else
	{
		noneBezierOut.Update();
		bossPtr->bossObj->position =
			noneBezierOut.InterPolation(BezierCurve::EaseOut);
	}

	if (noneBezierOut.GetisEnd() == true)
	{
		step = Rush1;
	}
}

// ラッシュ
void BossRush::Rush1Update()
{
	stayRushTimer++;
	if (stayRushTimer >= stayRushMaxTimer)
	{
		stayRushTimer = stayRushMaxTimer;

		const Vec3 targetPos = { 0,5,-40 };
		Vec3 vec = targetPos - bossPtr->bossObj->position;
		bossPtr->bossObj->position += vec.Norm() * rushSpeed;

		if (vec.GetLength() <= 0.5f)
		{
			bossPtr->bossObj->position = { 50,5,0 };
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
		Vec3 vec = targetPos - bossPtr->bossObj->position;
		bossPtr->bossObj->position += vec.Norm() * rushSpeed;

		if (vec.GetLength() <= 0.5f)
		{
			bossPtr->bossObj->position = targetPos;
			stayRushTimer = 0;
			step = End;
		}
	}
}
void BossRush::EndUpdate()
{
	isEnd = true;
}