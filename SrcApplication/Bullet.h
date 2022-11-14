#pragma once
#include <SpMath.h>
#include <Object3D.h>
#include <memory>

class Bullet
{
private:
	std::unique_ptr<Object3D> bulletObj;
	Vec3 vec;
	float speed;
	float collisionRadius;

private:
	// 生存関連
	bool isActive;
	int activeTimer;
	int activeMaxTimer;
	int bulletDamage;

public:
	Bullet(const Vec3 pos, const Vec3 vec, const int& activeMaxTimer, Model* bulletModel);
	void Update();
	void DrawModel();

public:
	// ゲッター
	inline bool GetisActive() { return isActive; }
	inline Vec3 GetPosition() { return bulletObj->position; }
	inline float GetCollisionRadius() { return collisionRadius; }
	inline int GetBulletDamage() { return bulletDamage; }

public:
	// セッター
	inline void SetScale(const Vec3& scale) { bulletObj->scale = scale; collisionRadius = scale.x; }
	inline void SetisActive(const bool& isActive) { this->isActive = isActive; }
	inline void SetBulletDamage(const int& bulletDamage) { this->bulletDamage = bulletDamage; }
};

