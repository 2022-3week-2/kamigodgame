#pragma once
#include "SpMath.h"
#include <Object3D.h>
#include <memory>

class Rock
{
private:
	std::unique_ptr<Object3D> rockObj;
	float gravity;

private:
	// 生存関連
	bool isActive;

public:
	Rock(const Vec3 pos, Model* rockModel);
	void Update();
	void DrawModel();

public:
	// ゲッター
	inline bool GetisActive() { return isActive; }

public:
	// セッター
	inline void SetisActive(const bool& isActive) { this->isActive = isActive; }
};

