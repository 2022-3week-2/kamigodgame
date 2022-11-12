#pragma once
#include <SpMath.h>
#include <Object3D.h>
#include <memory>

class Beam
{
private:
	std::unique_ptr<Object3D> beamObj;

private:
	// �����֘A
	bool isActive;
	int activeTimer;
	int activeMaxTimer;

public:
	Beam(const Vec3 pos, const Vec3 vec, Model* beamModel);
	void Update();
	void DrawModel();

public:
	// �Q�b�^�[
	inline bool GetisActive() { return isActive; }
};

