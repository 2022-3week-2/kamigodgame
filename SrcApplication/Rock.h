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
	// �����֘A
	bool isActive;

public:
	Rock(const Vec3 pos, Model* rockModel);
	void Update();
	void DrawModel();

public:
	// �Q�b�^�[
	inline bool GetisActive() { return isActive; }

public:
	// �Z�b�^�[
	inline void SetisActive(const bool& isActive) { this->isActive = isActive; }
};

