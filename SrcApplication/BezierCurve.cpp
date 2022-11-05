#include "BezierCurve.h"
#include "Easing.h"
using namespace std;

BezierCurve::BezierCurve()
{
}

BezierCurve::BezierCurve(const float& interpolateTime) :
	interpolateTime(interpolateTime), startIndex(1), isEnd(false)
{
	ease.SetEaseTimer(interpolateTime);
	ease.SetPowNum(3);
}

void BezierCurve::ReSet()
{
	timer = 0;
	timeRate = 0;
	ease.ReSet();
	isEnd = false;
}

void BezierCurve::Update()
{
	if (points.size() < 2) return;

	ease.Update();
	if (ease.GetisEnd() == true)
	{
		isEnd = true;
	}
}

Vec3 BezierCurve::InterPolation(const int& type)
{
	if (RecursiveLerp(points, type).size() < 2) return { 0,0,0 };

	// “ñ‰ñ
	switch (type)
	{
	case 0:
		return ease.Lerp(RecursiveLerp(points, type)[0], RecursiveLerp(points, type)[1]);
		break;
	case 1:
		return ease.In(RecursiveLerp(points, type)[0], RecursiveLerp(points, type)[1]);
		break;
	case 2:
		return ease.Out(RecursiveLerp(points, type)[0], RecursiveLerp(points, type)[1]);
		break;
	default:
		break;
	}
}

vector<Vec3> BezierCurve::RecursiveLerp(const vector<Vec3>& points, const int& type)
{
	vector<Vec3> tempPoints;

	if (points.size() < 3)
	{
		return points;
	}
	else
	{
		switch (type)
		{
		case 0:
			for (size_t i = 0; i < points.size() - 1; i++)
			{
				tempPoints.push_back(ease.Lerp(points[i], points[i + 1]));
			}
			return RecursiveLerp(tempPoints, type);
			break;

		case 1:
			for (size_t i = 0; i < points.size() - 1; i++)
			{
				tempPoints.push_back(ease.In(points[i], points[i + 1]));
			}
			return RecursiveLerp(tempPoints, type);
			break;

		case 2:
			for (size_t i = 0; i < points.size() - 1; i++)
			{
				tempPoints.push_back(ease.Out(points[i], points[i + 1]));
			}
			return RecursiveLerp(tempPoints, type);
			break;

		default:
			break;
		}
	}
}