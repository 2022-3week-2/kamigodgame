#pragma once
#include "Boss.h"
class Boss;

class IBossMotion
{
protected:
	int step;		// モーションのステップ
	Boss* bossPtr;	// ボスのポインタ
	bool isEnd;		// モーション終了フラグ

public:
	virtual ~IBossMotion() {}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void DrawModel() = 0;

public:
	// ゲッター
	inline bool GetisEnd() { return isEnd; }

public:
	// セッター
	inline void SetBossPtr(Boss* bossPtr) { this->bossPtr = bossPtr; }
};