#pragma once
#include <SpMath.h>
#include <Object3D.h>
#include <memory>

class Beam
{
private:
	std::unique_ptr<Object3D> beamObj;
	float beamThickness;

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
	inline Vec3 GetPosition() { return beamObj->position; }
	inline Vec3 GetScale() { return beamObj->scale; }
	inline bool GetBeamThickness() { return beamThickness; }
};

