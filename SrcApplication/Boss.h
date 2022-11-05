#pragma once
#include "SpMath.h"
#include "Bullet.h"
#include "IBossMotion.h"
#include "BossRush.h"
#include <Object3D.h>
#include <memory>

class IBossMotion;
class BossRush;

class Boss
{
private:
	friend BossRush;

private:
	std::unique_ptr<Object3D> bossObj;
	std::unique_ptr<Model> bossModel;
	std::unique_ptr<IBossMotion> bossMotion;

public:
	Boss();
	void Load();
	void Init();
	void Update();
	void DrawModel();

public:
	// ゲッター
	inline Vec3 GetPosition() { return bossObj->position; }

public:
	// セッター
};

