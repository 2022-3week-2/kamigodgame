#include "stdafx.h"
#include "GameScene.h"
#include "SpMath.h"
#include <TextDrawer.h>

void GameScene::Init()
{
	SpTextureManager::Init();
	camera.UseDefaultParams();
	camera.renderWidth = 300;
	camera.renderHeight = 600;

	mCube = Model("cube");
	mSky = Model("skydome");
	mRegularSurface_20 = Model("20Surface");

	obj.model = &mCube;
	sky.model = &mSky;
	boss.model = &mRegularSurface_20;
	player = std::move(std::make_unique<Player>());
	player->Load();
	player->Init();

	whiteTex = SpTextureManager::LoadTexture("Resources/white.png", "white");
}

void GameScene::Update()
{
	boss.position = { 0,0,0 };

	player->Update();
	player->SetBossObj(&boss);

	const float lenght = 10;
	const float offset = 0.09f;
	Vec3 cameraNewPosition =
	{
		(cosf(-player->GetRotation().y) * lenght + player->GetPosition().x),
		(player->GetPosition().y + lenght),
		(sinf(-player->GetRotation().y) * lenght + player->GetPosition().z),
	};

	camera.position += (cameraNewPosition - camera.position) * 0.09f;

	camera.targetMode = CameraTargetMode::LookAt;
	camera.rotation = boss.position;
	camera.UpdateMatrix();

	obj.UpdateMatrix();
	sky.UpdateMatrix();
	boss.UpdateMatrix();
}

void GameScene::DrawBack()
{
}

void GameScene::Draw3D()
{
	Camera::Set(camera);

	//obj.Draw();
	sky.Draw();

	boss.Draw("white");

	player->DrawModel();
}

void GameScene::DrawSprite()
{
	//TextDrawer::DrawString("hogeほげーー", 100, 100, Align::TopLeft);

	StringOptions stringOptions = { 20,2,2 };
	TextDrawer::DrawString("アローキー：移動", 20, 20, Align::TopLeft);
	TextDrawer::DrawString("[Z]：ショット", 20, 84, Align::TopLeft);
	TextDrawer::DrawString("[X]：ジャンプ", 20, 148, Align::TopLeft);
}
