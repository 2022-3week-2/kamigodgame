#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include <TextDrawer.h>
using namespace Input;

Player::Player() :
	speed(0.3), gravity(0), jumpCount(0), jumpMaxCount(1),
	moveAngle(0.01), moveLenght(10),
	shotTimer(5), shotMaxTimer(5)
{
}
Player::~Player()
{
}

void Player::Load()
{
	playerModel.reset(new Model("TempPlayer"));
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

void Player::MoveUpdate()
{
	const int offset = 200;
	if (Key::Down(DIK_RIGHT) || Pad::GetLStick().x >= offset)
	{
		playerObj->position.x += speed;
	}
	if (Key::Down(DIK_LEFT) || Pad::GetLStick().x <= -offset)
	{
		playerObj->position.x -= speed;
	}
	if (Key::Down(DIK_UP) || Pad::GetLStick().y >= offset)
	{
		playerObj->position.z += speed;

	}
	if (Key::Down(DIK_DOWN) || Pad::GetLStick().y <= -offset)
	{
		playerObj->position.z -= speed;
	}

	if (Pad::GetLStick().x >= offset || Pad::GetLStick().x <= -offset ||
		Pad::GetLStick().y >= offset || Pad::GetLStick().y <= -offset)
	{
		frontVec =
		{
			Pad::GetLStick().x,
			0,
			Pad::GetLStick().y,
		};
		playerObj->rotation.y = atan2f(frontVec.Norm().z, -frontVec.Norm().x);
	}
}
void Player::JumpUpdate()
{
	if (Key::Triggered(DIK_X) || Pad::Triggered(Button::A))
	{
		if (jumpCount < jumpMaxCount)
		{
			gravity = 0.75;
			jumpCount++;
		}
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
		jumpCount = 0;
	}
}
void Player::ShotUpdate()
{
	// 生成
	if (Key::Down(DIK_Z) || Pad::Down(Button::X))
	{
		shotTimer++;
		if (shotTimer >= shotMaxTimer)
		{
			//Vec3 frontVec = (Vec3)bossPtr->GetPosition() - playerObj->position;

			bullets.emplace_back(std::move(std::make_unique<Bullet>(
				playerObj->position, frontVec.Norm(), bulletModel.get())));
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