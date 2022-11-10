#pragma once
#include "IBossMotion.h"
#include "Rock.h"
#include <memory>
#include <list>

class BossRockFall : public IBossMotion
{
private:
	enum MotionStep
	{
		Start,
		GeneRock,
		RockFall,
		End,
	};

private:
	std::list<std::unique_ptr<Rock>> rocks;
	int rockFallTimer;		// 落石するタイマー
	int rockFallMaxTimer;	// マックスタイマー

	int generateTimer;
	int generateMaxTimer;

private:
	void StartUpdate();
	void GeneRockUpdate();
	void RockFallUpdate();
	void EndUpdate();

	void FourRocksPattern(const float& angle);
	void EightRocksPattern(const float& angle);
	void SixteenRocksPattern(const float& angle);

public:
	void Init() override;
	void Update() override;
	void DrawModel() override;
};

