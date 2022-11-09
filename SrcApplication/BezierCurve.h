#pragma once
#include <vector>
#include "Vec3.h"
#include "Easing.h"

class BezierCurve
{
public:
	enum InterPolationType
	{
		Lerp,
		EaseIn,
		EaseOut,
	};

private:
	std::vector<Vec3> points;
	size_t startIndex;
	float interpolateTime;
	float timeRate = 0;
	int timer = 0;
	bool isEnd;

	Easing ease;

public:
	BezierCurve();
	BezierCurve(const float& interpolateTime);
	void ReSet();
	void Update();
	Vec3 InterPolation(const int& type);
	inline void AddPoint(const Vec3& pos) { points.push_back(pos); }
	inline bool GetisEnd() { return isEnd; }
	inline void SetEaseTime(const float& easeTime) { ease.SetEaseTimer(easeTime); }
	inline void SetEasePowNum(const float& pownum) { ease.SetPowNum(pownum); }
	inline void ClearPoints() { points.clear(); }

private:
	std::vector<Vec3> RecursiveLerp(const std::vector<Vec3>& points, const int& type);
};