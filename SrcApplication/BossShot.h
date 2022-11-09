#pragma once
#include "IBossMotion.h"
#include "Bullet.h"
#include <memory>
#include <list>
#include <vector>

class BossShot : public IBossMotion
{
private:
	enum MotionStep
	{
		Start,
		Move,
		Shot,
		End,
	};

private:
	int step;
	std::list<std::unique_ptr<Bullet>> bullets;

	struct TargetPosParam
	{
		Vec3 pos = { 0,0,0 };
		Vec3 shotVec = { 0,0,0 };
	};
	std::vector<TargetPosParam> targetPosParams;
	std::vector<Vec3> targetPoses;

	int shotCount;
	int shotMaxCount;

	int shotTimer;
	int shotMaxTimer;

private:
	void StartUpdate();
	void MoveUpdate();
	void ShotUpdate();
	void EndUpdate();

	void TargetPosPattern1();
	void TargetPosPattern2();
	void TargetPosPattern3();
public:
	void Init() override;
	void Update() override;
	void DrawModel() override;
};

