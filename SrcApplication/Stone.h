#pragma once
#include "SpMath.h"
#include "Easing.h"
#include <Object3D.h>
#include <memory>

class Stone
{
private:
	std::unique_ptr<Object3D> stoneObj;
	Vec3 generatePos;
	int index;
	float collisionRadius;

	bool isGenerate;
	Easing generateEase;
	bool isCarry;


private:
	// 投げる処理関連
	struct ShotParam
	{
		Vec3 vec;
		float speed;
		float gravity;
	};

	ShotParam shotParam;
	bool isShot;

private:
	void GenerateUpdate();

public:
	Stone(const Vec3 pos, Model* stoneModel, const int& index);
	void Update();
	void ShotUpdate();
	void DrawModel();

public:
	// ゲッター
	inline Vec3 GetPosition() { return stoneObj->position; }
	inline float GetCollisionRadius() { return collisionRadius; }
	inline bool GetisShot() { return isShot; }
	inline bool GetisCarry() { return isCarry; }

public:
	// セッター
	inline void SetPosition(const Vec3& pos) { stoneObj->position = pos; }
	inline void SetScale(const Vec3& scale) { stoneObj->scale = scale; }
	inline void SetisCarry(const bool& isCarry) { this->isCarry = isCarry; }
	inline void SetisShot(const bool& isShot) { this->isShot = isShot; }
	inline void SetShotParam(const ShotParam& shotParam) { this->shotParam = shotParam; }

};

