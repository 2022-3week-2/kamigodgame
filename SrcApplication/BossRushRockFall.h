#pragma once
#include "IBossMotion.h"
#include "BezierCurve.h"
#include "Easing.h"
#include "Rock.h"
#include <memory>
#include <list>

class BossRushRockFall : public IBossMotion
{
private:
	enum MotionStep
	{
		Start,
		Rush1,
		Move,
		Rush2,
		End,
	};
private:
	BezierCurve noneBezierIn;
	BezierCurve noneBezierOut;

	int stayRushTimer;		// ラッシュする前のクールタイム
	int stayRushMaxTimer;	// マックスクールタイム
	Vec3 angleVec;

	Vec3 startPos;
	Vec3 endPos;
	float moveSpeed;
	float rushSpeed;

private:
	std::list<std::unique_ptr<Rock>> rocks;
	int rockFallTimer;
	int rockFallMaxTimer;

private:
	void BezierInit(const Vec3& endPos);
	void StartUpdate();
	void Rush1Update();
	void MoveUpdate();
	void Rush2Update();
	void EndUpdate();

	void GeneRockUpdate();
	void RockFallUpdate();

public:
	void Init() override;
	void Update() override;
	void DrawModel() override;
};

