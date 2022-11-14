#pragma once
#include "SpMath.h"
#include "Bullet.h"
#include "Boss.h"
#include "Field.h"
#include "Gauge.h"
#include <SphereCollider.h>
#include <Object3D.h>
#include <memory>
#include <list>

class Boss;

class Player
{
private:
	std::unique_ptr<Object3D> playerObj;
	std::unique_ptr<Model> playerModel;
	std::unique_ptr<Model> bulletModel;

	Boss* bossPtr;	// ボスのポインタ
	Field* fieldPtr;	// フィールドのポインタ

private:
	// HP関連
	std::unique_ptr<Gauge> hpGauge;
	int hp;
	int maxhp;

private:
	// 移動関連
	Vec3 frontVec;		// 正面ベクトル
	float speed;		// 移動速度
	float moveAngle;	// ボスを中心に左右移動の時に回転する角度
	float moveLenght;	// ボスを中心に前後移動の時のボスとの距離

	float collisionRadius;

private:
	// ジャンプ関連
	float gravity;	// 重力
	int jumpCount;		// ジャンプした回数
	int jumpMaxCount;	// マックス回数
	float dushSpeed;

private:
	// ショット関連
	std::list<std::unique_ptr<Bullet>> bullets;
	int shotTimer;
	int shotMaxTimer;

	int pushTimer;
	int pushMaxTimer;


private:
	// ダメージ関連
	bool isDamage;
	bool isDamageShain;
	int damageShainTimer;
	int damageShainMaxTimer;
	SphereCollider playerCollider;


private:
	void MoveUpdate();	// 移動処理
	void JumpUpdate();	// ジャンプ処理
	void ShotUpdate();	// 弾を打つ処理
	void DamageUpdate();	// ダメージを受ける処理

public:
	Player();
	~Player();
	void Load();
	void Init();
	void Update();
	void DrawModel();
	void DrawFrontSprite();

	inline void SetisDamage(const int damage)
	{
		if (isDamage == false)
		{
			isDamage = true;
			isDamageShain = true;
			hp -= damage;
		}
	}

public:
	// ゲッター
	inline Vec3 GetPosition() { return playerObj->position; }
	inline Vec3 GetRotation() { return playerObj->rotation; }
	inline std::list<std::unique_ptr<Bullet>>* GetBullets() { return &bullets; }
	inline SphereCollider GetPlayerCollider() { return playerCollider; }

public:
	// セッター
	inline void SetBossPtr(Boss* bossPtr) { this->bossPtr = bossPtr; }
	inline void SetFieldPtr(Field* fieldPtr) { this->fieldPtr = fieldPtr; }

};

