#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Collision.h"
#include <TextDrawer.h>
using namespace Input;

Player::Player() :
	speed(0.3), gravity(0), jumpCount(0), jumpMaxCount(1), dushSpeed(1.5f),
	moveAngle(0.01), moveLenght(10), collisionRadius(1),
	shotTimer(5), shotMaxTimer(5), pushTimer(0), pushMaxTimer(60),
	maxhp(100), hp(maxhp),
	hpGauge(std::move(std::make_unique<Gauge>(Vec3(316, 64, 0), Vec3(4, 4, 4), "playerGaugeFrame"))),
	isDamage(false), isDamageShain(false), damageShainTimer(0), damageShainMaxTimer(120)
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
	hp = maxhp;
}
void Player::Update()
{
	MoveUpdate();	// 移動処理
	JumpUpdate();	// ジャンプ処理
	ShotUpdate();	// 弾を打つ処理
	DamageUpdate();

	hpGauge->SetGaugeFrontColor({ 10,160,30 });
	hpGauge->SetGaugeBackColor({ 210,210,15 });
	hpGauge->SetGaugeExrate((float)hp / maxhp);
	hpGauge->Update();
	if (hp <= 0)
	{
		hp = 0;
	}

	playerCollider.pos = playerObj->position;
	playerCollider.r = playerObj->scale.x;

	playerObj->UpdateMatrix();
}
void Player::DrawModel()
{
	for (const auto& currentBullet : bullets)
	{
		currentBullet->DrawModel();
	}

	//stone->DrawModel();

	if (damageShainTimer % 10 < 5)
	{
		playerObj->Draw();
	}
}
void Player::DrawFrontSprite()
{
	hpGauge->DrawFrontSprite();
}

void Player::MoveUpdate()
{
	const int offset = 200;
	const float pushRate = (float)pushTimer / pushMaxTimer;
	const float moveSpeed = max((1 - pushRate) * speed, 0.1f);
	//const float moveSpeed = 0.1f;
	if (Key::Down(DIK_RIGHT) || Pad::GetLStick().x >= offset)
	{
		playerObj->position.x += moveSpeed;
	}
	if (Key::Down(DIK_LEFT) || Pad::GetLStick().x <= -offset)
	{
		playerObj->position.x -= moveSpeed;
	}
	if (Key::Down(DIK_UP) || Pad::GetLStick().y >= offset)
	{
		playerObj->position.z += moveSpeed;

	}
	if (Key::Down(DIK_DOWN) || Pad::GetLStick().y <= -offset)
	{
		playerObj->position.z -= moveSpeed;
	}

	Vec3 dis = playerObj->position;
	const float lenght = 29;
	if (dis.GetLength() >= lenght)
	{
		playerObj->position = dis.Norm() * lenght;
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
	else if (Key::Down(DIK_RIGHT) || Key::Down(DIK_LEFT) ||
		Key::Down(DIK_UP) || Key::Down(DIK_DOWN))
	{
		frontVec =
		{
			(float)(Key::Down(DIK_RIGHT) - Key::Down(DIK_LEFT)),
			0,
			(float)(Key::Down(DIK_UP) - Key::Down(DIK_DOWN)),
		};
		playerObj->rotation.y = atan2f(frontVec.Norm().z, -frontVec.Norm().x);
	}
}
void Player::JumpUpdate()
{
	if (jumpCount < jumpMaxCount)
	{
		if (Key::Triggered(DIK_X) || Pad::Triggered(Button::A))
		{
			gravity = 0.75f;
			jumpCount++;
		}
	}
	else if (jumpCount >= jumpMaxCount)
	{
		if (Key::Triggered(DIK_X) || Pad::Triggered(Button::A))
		{
			dushSpeed = 1.5f;
			jumpCount++;
		}
	}
	if (jumpCount > jumpMaxCount)
	{
		dushSpeed -= 0.005;
		playerObj->position += frontVec * dushSpeed;
	}


	gravity -= 0.05f;
	if (gravity <= -1)
	{
		gravity = -1;
	}
	playerObj->position.y += gravity;

	if (playerObj->position.y < 0)
	{
		gravity = 0;
		playerObj->position.y = 0;
		jumpCount = 0;
	}

	/*if ((playerObj->position.x - fieldPtr->GetPosition().x) *
		(playerObj->position.x - fieldPtr->GetPosition().x) +
		(playerObj->position.z - fieldPtr->GetPosition().z) *
		(playerObj->position.z - fieldPtr->GetPosition().z) <=
		(playerObj->scale.x + 30) * (playerObj->scale.x + 30))
	{
		if (playerObj->position.y < 0)
		{
			gravity = 0;
			playerObj->position.y = 0;
			jumpCount = 0;
		}
	}
	else
	{
		if (playerObj->position.y < -5)
		{
			playerObj->position = { 0,0,-10 };
			jumpCount = 0;
		}
	}*/

}
void Player::ShotUpdate()
{
	if (Key::Down(DIK_Z) || Pad::Down(Button::X))
	{
		pushTimer++;
		if (pushTimer >= pushMaxTimer)
		{
			pushTimer = pushMaxTimer;
		}
	}
	if (Key::Released(DIK_Z) || Pad::Released(Button::X))
	{
		bullets.emplace_back(std::move(std::make_unique<Bullet>(
			playerObj->position, frontVec.Norm(), 40, bulletModel.get())));
		if (pushTimer < pushMaxTimer)
		{
			bullets.back()->SetBulletDamage(1);
		}
		else
		{
			bullets.back()->SetScale({ 3,3,3 });
			bullets.back()->SetBulletDamage(5);
		}
		pushTimer = 0;
	}

	// 生成
	//if (Key::Down(DIK_Z) || Pad::Down(Button::X))
	//{
	//	shotTimer++;
	//	if (shotTimer >= shotMaxTimer)
	//	{
	//		bullets.emplace_back(std::move(std::make_unique<Bullet>(
	//			playerObj->position, frontVec.Norm(), 40, bulletModel.get())));
	//		shotTimer = 0;
	//	}
	//}

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
void Player::DamageUpdate()
{
	if (isDamageShain == false) return;

	damageShainTimer++;
	if (damageShainTimer >= damageShainMaxTimer)
	{
		damageShainTimer = 0;
		isDamageShain = false;
		isDamage = false;
	}
}
