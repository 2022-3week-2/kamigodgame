#pragma once
class Random
{
public:
	static void Init();
	static int Range(int min, int max);			// int型の乱数を取得
	static float RangeF(float min, float max);	// float型の乱数を取得
	static bool Bool(float rate); // 確率でtrueを返す
};