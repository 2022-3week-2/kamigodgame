#pragma once
#include "IBossMotion.h"
#include "Bullet.h"
#include "Beam.h"
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
	std::list<std::unique_ptr<Beam>> beams;

	std::vector<Vec3> targetPoses;
	Vec3 targetVec;

	int shotCount;
	int shotMaxCount;

	int shotTimer;
	int shotMaxTimer;

private:
	void StartUpdate();
	void MoveUpdate();
	void ShotUpdate();
	void EndUpdate();

	void BulletHitPlayer();
	void BeamHitPlayer();

public:
	void Init() override;
	void Update() override;
	void DrawModel() override;
};

