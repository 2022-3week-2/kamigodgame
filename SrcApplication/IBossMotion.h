#pragma once
#include "Boss.h"
class Boss;

class IBossMotion
{
protected:
	int step;		// ���[�V�����̃X�e�b�v
	Boss* bossPtr;	// �{�X�̃|�C���^
	bool isEnd;		// ���[�V�����I���t���O

public:
	virtual ~IBossMotion() {}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void DrawModel() = 0;

public:
	// �Q�b�^�[
	inline bool GetisEnd() { return isEnd; }

public:
	// �Z�b�^�[
	inline void SetBossPtr(Boss* bossPtr) { this->bossPtr = bossPtr; }
};