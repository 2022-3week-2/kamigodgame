#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Float2.h"
#include "Float3.h"
#include "Float4.h"
#include "Matrix.h"

#ifndef PI
#define PI 3.14159265359
#endif

#ifndef PIf
#define PIf 3.14159265359f
#endif

// �ʓx�@����x���@�ɕϊ�����֐�
inline float RadianToAngle(const float& radian)
{
	return radian * 360 / (2 * PI);
}
inline Vec2 RadianToAngle(const Vec2& radian)
{
	return { RadianToAngle(radian.x),RadianToAngle(radian.y) };
}
inline Vec3 RadianToAngle(const Vec3& radian)
{
	return { RadianToAngle(radian.x),RadianToAngle(radian.y),RadianToAngle(radian.z) };
}

// �x���@����ʓx�@�ɕϊ�����֐�
inline float AngleToRadian(const float& angle)
{
	return angle * (2 * PI) / 360;
}
inline Vec2 AngleToRadian(const Vec2& angle)
{
	return { AngleToRadian(angle.x),AngleToRadian(angle.y) };
}
inline Vec3 AngleToRadian(const Vec3& angle)
{
	return { AngleToRadian(angle.x),AngleToRadian(angle.y),AngleToRadian(angle.z) };
}

