#pragma once
#include "SpMath.h"
#include "Bullet.h"
#include <Object3D.h>
#include <memory>
#include <list>

class Player
{
private:
	std::unique_ptr<Object3D> playerObj;
	std::unique_ptr<Model> playerModel;
	std::unique_ptr<Model> bulletModel;

	Object3D* bossObjPtr;	// �{�X�̃|�C���^

private:
	// �ړ��֘A
	float speed;		// �ړ����x
	float moveAngle;	// �{�X�𒆐S�ɍ��E�ړ��̎��ɉ�]����p�x
	float moveLenght;	// �{�X�𒆐S�ɑO��ړ��̎��̃{�X�Ƃ̋���

private:
	// �W�����v�֘A
	float gravity;	// �d��

private:
	// �V���b�g�֘A
	std::list<std::unique_ptr<Bullet>> bullets;
	int shotTimer;
	int shotMaxTimer;

private:
	void MoveUpdate();	// �ړ�����
	void JumpUpdate();	// �W�����v����
	void ShotUpdate();	// �e��ł���

public:
	Player();
	~Player();
	void Load();
	void Init();
	void Update();
	void DrawModel();

public:
	// �Q�b�^�[
	inline Vec3 GetPosition() { return playerObj->position; }
	inline Vec3 GetRotation() { return playerObj->rotation; }

public:
	// �Z�b�^�[
	inline void SetBossObj(Object3D* bossObjPtr) { this->bossObjPtr = bossObjPtr; }
};

