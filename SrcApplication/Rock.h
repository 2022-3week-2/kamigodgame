#pragma once
#include "SpMath.h"
#include <Object3D.h>
#include <memory>

class Rock
{
private:
	std::unique_ptr<Object3D> rockShadowObj;
	std::unique_ptr<Object3D> rockObj;

private:
	// 生存関連
	bool isActive;
	float gravity;
	bool isFall;

public:
	Rock(const Vec3 pos, Model* rockModel, Model* rockShadowModel);
	void Update();
	void DrawModel();

public:
	// ゲッター
	inline bool GetisActive() { return isActive; }

public:
	// セッター
	inline void SetisActive(const bool& isActive) { this->isActive = isActive; }
	inline void SetisFall(const bool& isFall) { this->isFall = isFall; }
};

