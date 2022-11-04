#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include <TextDrawer.h>
using namespace Input;

void Player::MoveUpdate()
{
	// 移動処理
	//playerObj->position.x += Pad::GetLStick().x * speed;
	//playerObj->position.z += Pad::GetLStick().y * speed;

	if (Key::Down(DIK_RIGHT))
	{
		moveAngle += speed * 2;
	}
	if (Key::Down(DIK_LEFT))
	{
		moveAngle -= speed * 2;
	}
	if (Key::Down(DIK_UP))
	{
		moveLenght += speed;
	}
	if (Key::Down(DIK_DOWN))
	{
		moveLenght -= speed;
	}
	if (bossObjPtr != nullptr)
	{
		playerObj->position.x = moveLenght * cosf(AngleToRadian(moveAngle)) + bossObjPtr->position.x;
		playerObj->position.z = moveLenght * sinf(AngleToRadian(moveAngle)) + bossObjPtr->position.y;

		Vec2 dis =
		{
			-(bossObjPtr->position.x - playerObj->position.x),
			bossObjPtr->position.z - playerObj->position.z,
		};
		playerObj->rotation.y = atan2f(dis.Norm().y, dis.Norm().x);
	}
}
void Player::JumpUpdate()
{
	if (Key::Triggered(DIK_X))
	{
		gravity = 0.75;
	}

	gravity -= 0.05;
	if (gravity <= -1)
	{
		gravity = -1;
	}
	playerObj->position.y += gravity;
	if (playerObj->position.y < 0)
	{
		playerObj->position.y = 0;
	}
}
void Player::ShotUpdate()
{
	// 生成
	if (Key::Down(DIK_Z))
	{
		shotTimer++;
		if (shotTimer >= shotMaxTimer)
		{
			Vec3 frontVec = (Vec3)bossObjPtr->position - playerObj->position;

			bullets.emplace_back(std::move(std::make_unique<Bullet>(
				playerObj->position, frontVec.Norm(), bulletModel.get()
				)));
			shotTimer = 0;
		}
	}

	// 更新
	for (const auto& currentBullet : bullets)
	{
		currentBullet->Update();
	}

	// 削除
	bullets.remove_if(
		[](std::unique_ptr<Bullet>& bullet)
		{
			return !bullet->GetisActive();
		});
}

Player::Player() :
	speed(0.5), gravity(0),
	moveAngle(0.01), moveLenght(-10),
	shotTimer(5), shotMaxTimer(5)
{
}
Player::~Player()
{
}

void Player::Load()
{
	playerModel.reset(new Model("tempPlayer"));
	bulletModel.reset(new Model("sphere"));
}
void Player::Init()
{
	playerObj = std::move(std::make_unique<Object3D>());
	playerObj->model = playerModel.get();
	playerObj->position.z = -10;
}
void Player::Update()
{

	MoveUpdate();	// 移動処理
	JumpUpdate();	// ジャンプ処理
	ShotUpdate();	// 弾を打つ処理

	playerObj->UpdateMatrix();
}

void Player::DrawModel()
{
	for (const auto& currentBullet : bullets)
	{
		currentBullet->DrawModel();
	}

	playerObj->Draw();
}