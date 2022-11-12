#include "stdafx.h"
#include "BossRushRockFallWavy.h"

void BossRushRockFallWavy::Init()
{
	step = Start;
	moveSpeed = 2;
	rushSpeed = 1;

	stayRushTimer = 0;		// ラッシュする前のクールタイム
	stayRushMaxTimer = 60;	// マックスクールタイム

	wavyObj = std::move(std::make_unique<Object3D>());
	wavyObj->scale = { 1,1,1 };
	wavyObj->model = bossPtr->GetWavyModel();
	downTimer = 0;
	downMaxTimer = 30;

	angleVec = bossPtr->GetPlayerPtr()->GetPosition() - Vec3(0, 0, 0);

	Vec3 targetPos = angleVec.Norm() * 30;
	targetPos.y = 5;

	BezierInit(targetPos);
}
void BossRushRockFallWavy::Update()
{
	// 関数ポインタ
	void (BossRushRockFallWavy:: * pFunc[])() =
	{
		// 登録
		&BossRushRockFallWavy::StartUpdate,
		&BossRushRockFallWavy::Rush1Update,
		&BossRushRockFallWavy::Move1Update,
		&BossRushRockFallWavy::Rush2Update,
		&BossRushRockFallWavy::Move2Update,
		&BossRushRockFallWavy::DownUpdate,
		&BossRushRockFallWavy::WavyUpdate,
		&BossRushRockFallWavy::EndUpdate,
	};

	RockFallUpdate();

	// 実行
	(this->*pFunc[step])();

	wavyObj->UpdateMatrix();
}
void BossRushRockFallWavy::DrawModel()
{
	for (const auto& currentRock : rocks)
	{
		currentRock->DrawModel();
	}

	if (step == Wavy)
	{
		wavyObj->Draw("white");
	}
}

void BossRushRockFallWavy::BezierInit(const Vec3& endPos)
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
void BossRushRockFallWavy::StartUpdate()
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
void BossRushRockFallWavy::Rush1Update()
{
	stayRushTimer++;
	if (stayRushTimer >= stayRushMaxTimer)
	{
		stayRushTimer = stayRushMaxTimer;

		const Vec3 targetPos = { -endPos.x,5,-endPos.z };
		Vec3 vec = targetPos - bossPtr->GetBossObj()->position;
		Vec3 lenght = targetPos - bossPtr->GetBossObj()->position;
		bossPtr->GetBossObj()->position += vec.Norm() * rushSpeed;

		if (lenght.GetLength() <= 0.5f)
		{
			BezierInit({ endPos.Cross({ 0,1,0 }).x,5,endPos.Cross({ 0,1,0 }).z });
			stayRushTimer = 0;
			GeneRockUpdate();
			step = Move1;
		}
	}
}
void BossRushRockFallWavy::Move1Update()
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
void BossRushRockFallWavy::Rush2Update()
{
	stayRushTimer++;
	if (stayRushTimer >= stayRushMaxTimer)
	{
		stayRushTimer = stayRushMaxTimer;

		const Vec3 targetPos = { -endPos.x,5,-endPos.z };
		Vec3 vec = targetPos - bossPtr->GetBossObj()->position;
		Vec3 lenght = vec;
		bossPtr->GetBossObj()->position += vec.Norm() * rushSpeed;

		if (lenght.GetLength() <= 0.5f)
		{
			BezierInit({ 0,30,0 });
			stayRushTimer = 0;
			//bossPtr->GetBossObj()->position = targetPos;
			step = Move2;
		}
	}
}
void BossRushRockFallWavy::Move2Update()
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
		step = Down;
	}
}
void BossRushRockFallWavy::DownUpdate()
{
	downTimer++;
	if (downTimer >= downMaxTimer)
	{
		const float downSpeed = 3;
		bossPtr->GetBossObj()->position.y -= downSpeed;
		if (bossPtr->GetBossObj()->position.y <= 5)
		{
			bossPtr->GetBossObj()->position.y = 5;
			downTimer = 0;
			step = Wavy;
		}
	}
}
void BossRushRockFallWavy::WavyUpdate()
{
	const float addSpeed = 0.15f;
	wavyObj->scale.x += addSpeed;
	wavyObj->scale.z += addSpeed;
	if (wavyObj->scale.x >= 30)
	{
		wavyObj->brightnessCB.contents->w -= 0.05f;
		if (wavyObj->brightnessCB.contents->w <= 0)
		{
			step = End;
		}
	}
}
void BossRushRockFallWavy::EndUpdate()
{
	isEnd = true;
}

void BossRushRockFallWavy::GeneRockUpdate()
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
void BossRushRockFallWavy::RockFallUpdate()
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
