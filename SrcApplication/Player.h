#pragma once
#include "SpMath.h"
#include "Bullet.h"
#include <Object3D.h>
#include <memory>
#include <list>

class Player
{
private:
	std::unique_ptr<Object3D> playerObj;
	std::unique_ptr<Model> playerModel;
	std::unique_ptr<Model> bulletModel;

	Object3D* bossObjPtr;	// ボスのポインタ

private:
	// 移動関連
	float speed;		// 移動速度
	float moveAngle;	// ボスを中心に左右移動の時に回転する角度
	float moveLenght;	// ボスを中心に前後移動の時のボスとの距離

private:
	// ジャンプ関連
	float gravity;	// 重力

private:
	// ショット関連
	std::list<std::unique_ptr<Bullet>> bullets;
	int shotTimer;
	int shotMaxTimer;

private:
	void MoveUpdate();	// 移動処理
	void JumpUpdate();	// ジャンプ処理
	void ShotUpdate();	// 弾を打つ処理

public:
	Player();
	~Player();
	void Load();
	void Init();
	void Update();
	void DrawModel();

public:
	// ゲッター
	inline Vec3 GetPosition() { return playerObj->position; }
	inline Vec3 GetRotation() { return playerObj->rotation; }

public:
	// セッター
	inline void SetBossObj(Object3D* bossObjPtr) { this->bossObjPtr = bossObjPtr; }
};

