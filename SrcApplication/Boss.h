#pragma once
#include "SpMath.h"
#include "Player.h"
#include "IBossMotion.h"
#include <Object3D.h>
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
	std::unique_ptr<IBossMotion> bossMotion;
	Player* playerPtr;

private:
	// �p�����[�^�[
	float collisionRadius;
	bool isDamage;


private:
	// �����蔻��֘A
	void PlayerHitBoss();

private:
	void DamageUpdate();

public:
	Boss();
	void Load();
	void Init();
	void Update();
	void DrawModel();

public:
	// �Q�b�^�[
	inline Vec3 GetPosition() { return bossObj->position; }
	inline Object3D* GetBossObj() { return bossObj.get(); }
	inline Model* GetRockModel() { return rockModel.get(); }
	inline Model* GetRockShadowModel() { return rockShadowModel.get(); }

public:
	// �Z�b�^�[
	inline void SetPlayerPtr(Player* playerPtr) { this->playerPtr = playerPtr; }
	inline void SetRotation(const Vec3& rot) { bossObj->rotation = rot; }
};

