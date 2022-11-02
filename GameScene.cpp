#include "stdafx.h"
#include "GameScene.h"
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

	whiteTex = SpTextureManager::LoadTexture("Resources/white.png", "white");
}

void GameScene::Update()
{
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
	
	
}

void GameScene::DrawSprite()
{
	TextDrawer::DrawString("hogeÇŸÇ∞Å[Å[", 100, 100, Align::TopLeft);
}
