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
	// �����֘A
	bool isActive;
	float gravity;
	bool isFall;
	float collisionRadius;

public:
	Rock(const Vec3 pos, Model* rockModel, Model* rockShadowModel);
	void Update();
	void DrawModel();

public:
	// �Q�b�^�[
	inline bool GetisActive() { return isActive; }
	inline Vec3 GetPosition() { return rockObj->position; }
	inline float GetCollisionRadius() { return collisionRadius; }

public:
	// �Z�b�^�[
	inline void SetisActive(const bool& isActive) { this->isActive = isActive; }
	inline void SetisFall(const bool& isFall) { this->isFall = isFall; }
};

