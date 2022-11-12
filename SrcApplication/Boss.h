#pragma once
#include "SpMath.h"
#include "Player.h"
#include "IBossMotion.h"
#include "Gauge.h"
#include <SphereCollider.h>
#include <Object3D.h>
#include <Sprite.h>
#include <memory>

class IBossMotion;
class Player;

class Boss
{
private:
	std::unique_ptr<Object3D> bossObj;
	std::unique_ptr<Model> bossModel;
	std::unique_ptr<Model> rockModel;
	std::unique_ptr<Model> rockShadowModel;
	std::unique_ptr<Model> bulletModel;
	std::unique_ptr<Model> beamModel;
	std::unique_ptr<Model> wavyModel;
	std::unique_ptr<IBossMotion> bossMotion;
	Player* playerPtr;

private:
	std::unique_ptr<Gauge> hpGauge;

private:
	// パラメーター
	float collisionRadius;
	bool isDamage;
	float addScaleFrame;
	bool isScaleMotion;

private:
	// 形態関連
	int bossForm;
	int maxhp;
	int hp;

private:
	SphereCollider bossCollider;

private:
	// 当たり判定関連
	void PlayerHitBoss();
	void BossHitPlayer();
	void BossRockHitPlayer();

private:
	void FormUpdate();
	void MotionUpdate();
	void DamageUpdate();
	void HPGaugeInit();
	void HPGaugeUpdate();

public:
	Boss();
	void Load();
	void Init();
	void Update();
	void DrawModel();
	void DrawFrontSprite();

public:
	// ゲッター
	inline Vec3 GetPosition() { return bossObj->position; }
	inline Vec3 GetScale() { return bossObj->scale; }
	inline Object3D* GetBossObj() { return bossObj.get(); }
	inline Model* GetRockModel() { return rockModel.get(); }
	inline Model* GetRockShadowModel() { return rockShadowModel.get(); }
	inline Model* GetBulletModel() { return bulletModel.get(); }
	inline Model* GetBeamModel() { return beamModel.get(); }
	inline Model* GetWavyModel() { return wavyModel.get(); }
	inline Player* GetPlayerPtr() { return playerPtr; }
	inline int GetBossForm() { return bossForm; }

public:
	// セッター
	inline void SetPlayerPtr(Player* playerPtr) { this->playerPtr = playerPtr; }
	inline void SetPosition(const Vec3& position) { bossObj->position = position; }
	inline void SetScale(const Vec3& scale) { bossObj->scale = scale; }
	inline void SetRotation(const Vec3& rot) { bossObj->rotation = rot; }
	inline void SetisScaleMotion(const bool& isScaleMotion) { this->isScaleMotion = isScaleMotion; }
};

