#pragma once
#include "Float4.h"
class Matrix
{
private:
	class Row {
		float c[4];	
		float operator[](size_t index) const;
		float& operator[](size_t index);
	};

public:
//Constructors
	//�P�ʍs��ŏ�����
	Matrix();

	//Float4��4�ŏ�����
	Matrix(Float4 r0, Float4 r1, Float4 r2, Float4 r3);
	
	//Float4�̔z��ŏ�����
	Matrix(Float4* p);

	//float��16�ŏ�����
	Matrix(float r0c0, float r0c1, float r0c2, float r0c3,
		float r1c0, float r1c1, float r1c2, float r1c3,
		float r2c0, float r2c1, float r2c2, float r2c3,
		float r3c0, float r3c1, float r3c2, float r3c3);

	//float�̔z��ŏ�����
	Matrix(float* p);

//Operators
	Matrix operator - () const;

	Row operator[](size_t index) const;

	Row& operator[](size_t index);

//Functions

//Static Functions
	static Matrix Identity();

public:

	Row r[4];
};

