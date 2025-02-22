#include "GameScene.h"
#include "stdafx.h"
#include "SpMath.h"
#include <TextDrawer.h>
#include "Input.h"
#include "SrcApplication/Random.h"
#include <Model.h>

void GameScene::LoadResources()
{
	SpTextureManager::LoadTexture("Resources/white.png", "white"); 
	SpTextureManager::LoadTexture("Resources/Sprite/BossSprite/bossGaugeFrame.png", "gaugeFrame");
	SpTextureManager::LoadTexture("Resources/Sprite/PlayerSprite/playerGaugeFrame.png", "playerGaugeFrame");
	SpTextureManager::LoadTexture("Resources/Sprite/BossSprite/bossGaugeFrame.png", "bossGaugeFrame");

	ModelManager::Register("cube", "Cube");
	ModelManager::Register("skydome", "Skydome");
}

void GameScene::Init()
{
	Random::Init();	// ランダムの初期化
	camera.UseDefaultParams();
	camera.renderWidth = 300;
	camera.renderHeight = 600;

	obj.model = ModelManager::GetModel("Cube");
	sky.model = ModelManager::GetModel("Skydome");

	whiteTex = "white";
	
	GenerateObj();
	SetAllObjPtr();
}

void GameScene::Update()
{
	// プレイヤー
	player->Update();

	// ボス
	boss->Update();

	// フィールド
	field->Update();

	// コメントアウトしたカメラの処理
	{
		const float offset = 0.09f;
		// カメラ
		//const float lenght = 15;
		//Vec3 cameraNewPosition =
		//{
		//	(cosf(-player->GetRotation().y) * lenght + player->GetPosition().x),
		//	(player->GetPosition().y + lenght),
		//	(sinf(-player->GetRotation().y) * lenght + player->GetPosition().z),
		//};
		//camera.position += (cameraNewPosition - camera.position) * 0.09f;
		//camera.targetMode = CameraTargetMode::LookAt;
		//camera.target = boss->GetPosition();

		// ｙ軸を無視した時の、プレイヤーとボスの距離
		Vec2 dis =
		{
			boss->GetPosition().x - player->GetPosition().x,
			boss->GetPosition().z - player->GetPosition().z,
		};
		// 割合
		float exrate = max(dis.GetLength(), 15) / 15;
		// 高さ
		const float height = exrate * 20;
		const float lenght = exrate * 15;
		camera.position.x += (player->GetPosition().x - camera.position.x) * offset;
		camera.position.y += (height - camera.position.y) * offset;
		camera.position.z += (player->GetPosition().z - camera.position.z - lenght) * offset;

		camera.rotation = { AngleToRadian(65),0,0 };
	}
	//camera.position = { 0,40,0 };
	//camera.rotation = { AngleToRadian(90),0,0 };
	//camera.position = { 0,0,-50 };
	//camera.rotation = { 0,0,0 };
	camera.UpdateMatrix();

	obj.UpdateMatrix();
	sky.UpdateMatrix();
}

void GameScene::DrawBack()
{
}

void GameScene::Draw3D()
{
	Camera::Set(camera);

	//obj.Draw();
	sky.Draw();

	boss->DrawModel();

	player->DrawModel();

	field->DrawModel();
}

void GameScene::DrawSprite()
{
	boss->DrawFrontSprite();
	player->DrawFrontSprite();

	//TextDrawer::DrawString("hogeほげーー", 100, 100, Align::TopLeft);

	StringOptions so;
	so.fontOptions.resolution = 24;
	so.size = 24;
	//TextDrawer::DrawString("アローキー：移動", 20, 20, Align::TopLeft, so);
	//TextDrawer::DrawString("[Z]：ショット", 20, 44, Align::TopLeft, so);
	//TextDrawer::DrawString("[X]：ジャンプ", 20, 68, Align::TopLeft, so);
}

void GameScene::GenerateObj()
{
	// プレイヤー
	player = std::move(std::make_unique<Player>());
	player->Load();

	// ボス
	boss = std::move(std::make_unique<Boss>());
	boss->Load();

	// フィールド
	field = std::move(std::make_unique<Field>());
	field->Load();
}
void GameScene::SetAllObjPtr()
{
	// フィールド
	field->Init();

	// プレイヤー
	player->SetBossPtr(boss.get());
	player->SetFieldPtr(field.get());
	player->Init();

	// ボス
	boss->SetPlayerPtr(player.get());
	boss->Init();
}