#pragma once
#pragma once
const double WRL_PI = 3.14159265358979;

//������Ԃ�(-1 or 1, int)
int Sign(double n);

//percentage %�̊m����true��Ԃ�
bool Chance(int percentage);

/*
�������Œ�l�ƍō��l��ݒ肵�ĕԂ��B
RNG(1,3)�Ȃ�1, 2, 3�̂ǂꂩ���Ԃ�BpreciseMode��true�ɂ���Ƃ�萸���ɗ��������B
*/
int RNG(int min, int max, bool preciseMode = false);

/*Clip(100,0,5) -> 5, Clip(-5,0,5) -> 0*/
template<class T> T Clip(T base, T min, T max)
{
	return T(base < min ? min : base > max ? max : base);
}

//���������Y�����
//�����Ɗp�x(�x���@)����X�����߂�
double ConvertDegDistToX(double dist, double deg);

//�����Ɗp�x(�x���@)����Y�����߂�
double ConvertDegDistToY(double dist, double deg);

