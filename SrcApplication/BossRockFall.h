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
		RockFall,
		End,
	};

private:
	int step;

	std::list<std::unique_ptr<Rock>> rocks;
	int rockFallTimer;		// ���΂���^�C�}�[
	int rockFallMaxTimer;	// �}�b�N�X�^�C�}�[

	int generateTimer;
	int generateMaxTimer;

private:
	void StartUpdate();
	void RockFallUpdate();
	void EndUpdate();

public:
	void Init() override;
	void Update() override;
	void DrawModel() override;
};

