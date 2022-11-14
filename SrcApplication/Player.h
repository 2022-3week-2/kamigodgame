#pragma once
#include "SpMath.h"
#include "Bullet.h"
#include "Boss.h"
#include "Field.h"
#include "Gauge.h"
#include <SphereCollider.h>
#include <Object3D.h>
#include <memory>
#include <list>

class Boss;

class Player
{
private:
	std::unique_ptr<Object3D> playerObj;
	std::unique_ptr<Model> playerModel;
	std::unique_ptr<Model> bulletModel;

	Boss* bossPtr;	// �{�X�̃|�C���^
	Field* fieldPtr;	// �t�B�[���h�̃|�C���^

private:
	// HP�֘A
	std::unique_ptr<Gauge> hpGauge;
	int hp;
	int maxhp;

private:
	// �ړ��֘A
	Vec3 frontVec;		// ���ʃx�N�g��
	float speed;		// �ړ����x
	float moveAngle;	// �{�X�𒆐S�ɍ��E�ړ��̎��ɉ�]����p�x
	float moveLenght;	// �{�X�𒆐S�ɑO��ړ��̎��̃{�X�Ƃ̋���

	float collisionRadius;

private:
	// �W�����v�֘A
	float gravity;	// �d��
	int jumpCount;		// �W�����v������
	int jumpMaxCount;	// �}�b�N�X��
	float dushSpeed;

private:
	// �V���b�g�֘A
	std::list<std::unique_ptr<Bullet>> bullets;
	int shotTimer;
	int shotMaxTimer;

	int pushTimer;
	int pushMaxTimer;


private:
	// �_���[�W�֘A
	bool isDamage;
	bool isDamageShain;
	int damageShainTimer;
	int damageShainMaxTimer;
	SphereCollider playerCollider;


private:
	void MoveUpdate();	// �ړ�����
	void JumpUpdate();	// �W�����v����
	void ShotUpdate();	// �e��ł���
	void DamageUpdate();	// �_���[�W���󂯂鏈��

public:
	Player();
	~Player();
	void Load();
	void Init();
	void Update();
	void DrawModel();
	void DrawFrontSprite();

	inline void SetisDamage(const int damage)
	{
		if (isDamage == false)
		{
			isDamage = true;
			isDamageShain = true;
			hp -= damage;
		}
	}

public:
	// �Q�b�^�[
	inline Vec3 GetPosition() { return playerObj->position; }
	inline Vec3 GetRotation() { return playerObj->rotation; }
	inline std::list<std::unique_ptr<Bullet>>* GetBullets() { return &bullets; }
	inline SphereCollider GetPlayerCollider() { return playerCollider; }

public:
	// �Z�b�^�[
	inline void SetBossPtr(Boss* bossPtr) { this->bossPtr = bossPtr; }
	inline void SetFieldPtr(Field* fieldPtr) { this->fieldPtr = fieldPtr; }

};

