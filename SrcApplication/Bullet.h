#pragma once
#include "SpMath.h"
#include <Object3D.h>
#include <memory>

class Bullet
{
private:
	std::unique_ptr<Object3D> bulletObj;
	Vec3 vec;
	float speed;

private:
	// 生存関連
	bool isActive;
	int activeTimer;
	int activeMaxTimer;

public:
	Bullet(const Vec3 pos, const Vec3 vec, Model* bulletModel);
	void Update();
	void DrawModel();

public:
	// ゲッター
	inline bool GetisActive() { return isActive; }

public:
	// セッター
	inline void SetisActive(const bool& isActive) { this->isActive = isActive; }
};

