#pragma once
#include "IBossMotion.h"
#include "Easing.h"
#include "BezierCurve.h"

class BossRush : public IBossMotion
{
private:
	enum MotionStep
	{
		Start,
		Rush1,
		Rush2,
		End,
	};

private:
	int step;

private:
	BezierCurve noneBezierIn;
	BezierCurve noneBezierOut;

	Easing upOutEase;
	Easing downInEase;

	int stayRushTimer;		// ラッシュする前のクールタイム
	int stayRushMaxTimer;	// マックスクールタイム

	Vec3 startPos;
	float moveSpeed;
	float rushSpeed;

private:
	void StartInit();
	void StartUpdate();

	void Rush1Update();
	void Rush2Update();

	void EndInit();
	void EndUpdate();

public:
	void Init() override;
	void Update() override;
	void DrawModel() override;

};

