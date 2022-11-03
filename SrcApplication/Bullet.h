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
	// �����֘A
	bool isActive;
	int activeTimer;
	int activeMaxTimer;

public:
	Bullet(const Vec3 pos, const Vec3 vec, Model* bulletModel);
	void Update();
	void DrawModel();

public:
	// �Q�b�^�[
	inline bool GetisActive() { return isActive; }

public:
	// �Z�b�^�[
	inline void SetisActive(const bool& isActive) { this->isActive = isActive; }
};

