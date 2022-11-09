#pragma once
#include "IBossMotion.h"
#include "Easing.h"
#include "BezierCurve.h"

//class Boss;

class BossRush : public IBossMotion
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

	int stayRushTimer;		// ���b�V������O�̃N�[���^�C��
	int stayRushMaxTimer;	// �}�b�N�X�N�[���^�C��

	Vec3 startPos;
	float moveSpeed;
	float rushSpeed;

private:
	void BezierInit(const Vec3& endPos);
	void StartUpdate();
	void Rush1Update();
	void MoveUpdate();
	void Rush2Update();
	void EndUpdate();

public:
	void Init() override;
	void Update() override;
	void DrawModel() override;
};

