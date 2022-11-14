#pragma once
#include <SpMath.h>
#include <Object3D.h>
#include <memory>

class Beam
{
private:
	std::unique_ptr<Object3D> beamObj;

private:
	// 生存関連
	bool isActive;
	int activeTimer;
	int activeMaxTimer;

public:
	Beam(const Vec3 pos, const Vec3 vec, Model* beamModel);
	void Update();
	void DrawModel();

public:
	// ゲッター
	inline bool GetisActive() { return isActive; }
	inline Vec3 GetPosition() { return beamObj->position; }
	inline Vec3 GetScale() { return beamObj->scale; }
	inline float GetLenght() { return beamObj->scale.z; }
	inline bool GetBeamThickness() { return beamObj->scale.x; }
};

