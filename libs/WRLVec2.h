#pragma once
class Vec2
{
public:
	float x;
	float y;

	Vec2();
	Vec2(float x, float y);

	void SetX(float x);

	void SetY(float y);

	//(Sqrt���Ă΂��)
	void SetLength(float l);

	//�x�N�g���̉��Z
	const Vec2 operator+(const Vec2& v2) const;

	//�x�N�g���̌��Z
	const Vec2 operator-(const Vec2& v2) const;

	//Vec�̒�����(x��y���ꂼ��)mul�{
	const Vec2 operator*(float mul) const;

	const Vec2 operator/(float div) const;

	//�x�N�g���̉��Z
	Vec2& operator +=(const Vec2& v2);

	//�x�N�g���̌��Z
	Vec2& operator -=(const Vec2& v2);

	//Vec�̒�����(x��y���ꂼ��)mul�{
	Vec2& operator *=(float mul);

	Vec2& operator /=(float div);

	//���ς����߂�
	float Dot(const Vec2& v2) const;
	
	//�O�ς����߂�
	float Cross(const Vec2& v2) const;

	//(Sqrt���Ă΂��)
	Vec2& Norm();

	//(Sqrt���Ă΂��)
	Vec2 GetNorm() const;

	float GetLength() const;

	float GetSquaredLength() const;
};

