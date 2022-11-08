#include "stdafx.h"
#include "GameScene.h"
#include "SpMath.h"
#include <TextDrawer.h>
#include "Input.h"
#include "SrcApplication/Random.h"

void GameScene::Init()
{
	Random::Init();	// �����_���̏�����
	SpTextureManager::Init();
	camera.UseDefaultParams();
	camera.renderWidth = 300;
	camera.renderHeight = 600;

	mCube = Model("cube");
	mSky = Model("skydome");

	obj.model = &mCube;
	sky.model = &mSky;

	// �t�B�[���h
	field = std::move(std::make_unique<Field>());
	field->Load();
	field->Init();

	// �{�X
	boss = std::move(std::make_unique<Boss>());
	boss->Load();
	boss->Init();

	// �v���C���[
	player = std::move(std::make_unique<Player>());
	player->Load();
	player->Init();
	player->SetBossPtr(boss.get());
	player->SetFieldPtr(field.get());

	whiteTex = SpTextureManager::LoadTexture("Resources/white.png", "white");
}

void GameScene::Update()
{
	// �v���C���[
	player->Update();

	// �{�X
	boss->Update();

	// �t�B�[���h
	field->Update();

	// �R�����g�A�E�g�����J�����̏���
	{
		//const float offset = 0.09f;
		// �J����
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

		// �����𖳎��������́A�v���C���[�ƃ{�X�̋���
		//Vec2 dis =
		//{
		//	boss->GetPosition().x - player->GetPosition().x,
		//	boss->GetPosition().z - player->GetPosition().z,
		//};
		//// ����
		//float exrate = max(dis.GetLength(), 15) / 15;
		//// ����
		//const float height = exrate * 20;
		//const float lenght = exrate * 15;
		//camera.position.x += (player->GetPosition().x - camera.position.x) * offset;
		//camera.position.y += (height - camera.position.y) * offset;
		//camera.position.z += (player->GetPosition().z - camera.position.z - lenght) * offset;

		//camera.rotation = { AngleToRadian(65),0,0 };
	}
	camera.position = { 0,30,0 };
	camera.rotation = { AngleToRadian(90),0,0 };
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
	//TextDrawer::DrawString("hoge�ق��[�[", 100, 100, Align::TopLeft);

	StringOptions stringOptions = { 20,2,2 };
	TextDrawer::DrawString("�A���[�L�[�F�ړ�", 20, 20, Align::TopLeft);
	TextDrawer::DrawString("[Z]�F�V���b�g", 20, 84, Align::TopLeft);
	TextDrawer::DrawString("[X]�F�W�����v", 20, 148, Align::TopLeft);
}
