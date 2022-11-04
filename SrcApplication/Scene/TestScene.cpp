#include "TestScene.h"
#include "RTVManager.h"
#include "SpSwapChainManager.h"
#include "Input.h"
#include "RayCollider.h"
#include "TextDrawer.h"

void TestScene::Init()
{
	SpTextureManager::Init();

#pragma region �l������ʗp�J�����ݒ�
	camera.SetRenderSize(640, 360);
	camera.nearZ = 0.1f;
	camera.farZ = 1000.0f;
	camera.fov = PI / 2;

	camera.position.x = -10;
	camera.position.y = 10;
	camera.position.z = -10;
	camera.UpdateMatrix();

	camera.target = { 0, 0, 0 };

	camera.targetMode = CameraTargetMode::LookAt;

	RTVManager::CreateRenderTargetTexture(640, 360, "camSpr");
	cameraSpr = Sprite("camSpr");

	xCam.SetRenderSize(640, 360);
	xCam.nearZ = 0.1f;
	xCam.farZ = 1000.0f;
	xCam.fov = PI / 2;

	xCam.position.x = -10;
	xCam.position.y = 0;
	xCam.position.z = 0;
	xCam.rotation = { 0.0f, PI / 2, 0.0f };
	xCam.UpdateMatrix();

	RTVManager::CreateRenderTargetTexture(640, 360, "xCamSpr");
	xCamSpr = Sprite("xCamSpr");

	yCam.SetRenderSize(640, 360);
	yCam.nearZ = 0.1f;
	yCam.farZ = 1000.0f;
	yCam.fov = PI / 2;

	yCam.position.x = 0;
	yCam.position.y = 10;
	yCam.position.z = 0;
	yCam.rotation = { PI / 2, 0.0f, 0.0f };
	yCam.UpdateMatrix();

	RTVManager::CreateRenderTargetTexture(640, 360, "yCamSpr");
	yCamSpr = Sprite("yCamSpr");

	zCam.SetRenderSize(640, 360);
	zCam.nearZ = 0.1f;
	zCam.farZ = 1000.0f;
	zCam.fov = PI / 2;

	zCam.position.x = 0;
	zCam.position.y = 0;
	zCam.position.z = -10;
	zCam.rotation = { 0.0f, 0.0f, 0.0f };
	zCam.UpdateMatrix();

	RTVManager::CreateRenderTargetTexture(640, 360, "zCamSpr");
	zCamSpr = Sprite("zCamSpr");

	camera.projectionMode = ProjectionMode::Perspective;
	xCam.projectionMode = ProjectionMode::Orthographic;
	yCam.projectionMode = ProjectionMode::Orthographic;
	zCam.projectionMode = ProjectionMode::Orthographic;

	cameraSpr.position = {960, 180, 0.0f};
	xCamSpr.position = {960, 540, 0.0f};
	yCamSpr.position = {320, 180, 0.0f};
	zCamSpr.position = {320, 540, 0.0f};

	finalScene.SetRenderSize(1280, 720);
	finalScene.nearZ = 0.1f;
	finalScene.farZ = 1000.0f;
	finalScene.fov = PI / 2;

	finalScene.position.x = 0;
	finalScene.position.y = 0;
	finalScene.position.z = -10;
	finalScene.rotation = { 0.0f, 0.0f, 0.0f };
	finalScene.UpdateMatrix();
#pragma endregion

	mCube = Model("cube");

	sky = Model("skydome");

	mSphere = Model("sphere");

	skysphere.model = &sky;

	whiteTex = SpTextureManager::LoadTexture("Resources/white.png", "white");

	for (auto& p : points) {
		p.model = &mSphere;
		p.scale = { 0.3f, 0.3f, 0.3f };
		*p.brightnessCB.contents = { 1.f, 0.f, 0.f, 1.f };
		p.UpdateMatrix();
	}

	sphere.model = &mSphere;
}

void TestScene::Update()
{
#pragma region �l������ʗp�J�����ݒ�
	cameraSpr.position = { 960, 180 };
	xCamSpr.position = { 960, 540 };
	yCamSpr.position = { 320, 180 };
	zCamSpr.position = { 320, 540 };

	cameraSpr.scale = { 1.0f, 1.0f };
	xCamSpr.scale = { 1.0f, 1.0f };
	yCamSpr.scale = { 1.0f, 1.0f };
	zCamSpr.scale = { 1.0f, 1.0f };

	camera.position = (Vec3)camera.position + Vec3(
		(Input::Key::Down(DIK_D) - Input::Key::Down(DIK_A)) * 0.1f,
		(Input::Key::Down(DIK_E) - Input::Key::Down(DIK_Q)) * 0.1f,
		(Input::Key::Down(DIK_W) - Input::Key::Down(DIK_S)) * 0.1f
	);

	camera.rotation = (Vec3)camera.rotation + Vec3(
		(Input::Key::Down(DIK_1) - Input::Key::Down(DIK_2)) * 0.01f,
		(Input::Key::Down(DIK_3) - Input::Key::Down(DIK_4)) * 0.01f,
		(Input::Key::Down(DIK_5) - Input::Key::Down(DIK_6)) * 0.01f
	);
	camera.UpdateMatrix();
#pragma endregion

	timer++;
	timer = min(timer, 300);

	float t = (float)timer / 300;
	
	//����_
	vector<Vec3> p = {
		{-7.f, -0.f, 2.f},
		{-1.f, -6.f, -4.f},
		{1.5f, 4.f, 3.f},
		{6.f, 0.f, -4.f},
		{10.f, 0.f, -5.f}
	};

	for (int i = 0; i < 5; i++)
	{
		points[i].position = p[i];
		points[i].UpdateMatrix();
	}

	//�ŏI�I�ȍ��W
	sphere.position = Vec3::Spline(p, t);

	//�s��X�V
	cameraSpr.UpdateMatrix();
	xCamSpr.UpdateMatrix();
	yCamSpr.UpdateMatrix();
	zCamSpr.UpdateMatrix();
	skysphere.UpdateMatrix();
	sphere.UpdateMatrix();
}

void TestScene::DrawBack()
{
}

void TestScene::Draw3D()
{
	RTVManager::SetRenderTargetToTexture("camSpr");
	Camera::Set(camera);
	skysphere.Draw();
	sphere.Draw();
	for (auto& p : points) p.Draw("white");

	RTVManager::SetRenderTargetToTexture("xCamSpr");
	Camera::Set(xCam);
	skysphere.Draw();
	sphere.Draw();
	for (auto& p : points) p.Draw("white");

	RTVManager::SetRenderTargetToTexture("yCamSpr");
	Camera::Set(yCam);
	skysphere.Draw();
	sphere.Draw();
	for (auto& p : points) p.Draw("white");

	RTVManager::SetRenderTargetToTexture("zCamSpr");
	Camera::Set(zCam);
	skysphere.Draw();
	sphere.Draw();
	for (auto& p : points) p.Draw("white");

	Camera::Set(finalScene);
	RTVManager::SetRenderTargetToBackBuffer(GetSCM()->swapchain->GetCurrentBackBufferIndex());
}

void TestScene::DrawSprite()
{
	cameraSpr.Draw();
	xCamSpr.Draw();
	yCamSpr.Draw();
	zCamSpr.Draw();

	StringOptions arialOpt;
	arialOpt.fontOptions.name = "Arial";
	arialOpt.size = 32;
	arialOpt.fontOptions.resolution = 128;

	string str("");
	str += to_string(sphere.position.x);
	str += ", "; str += to_string(sphere.position.y);
	str += ", "; str += to_string(sphere.position.z);
	str += ", T = "; str += to_string(timer);
	TextDrawer::DrawString( str, 32, 32, Align::TopLeft, arialOpt);

	//TextDrawer::DrawString("0���ɂ�`�`�`�`0", 1180, 100, Align::TopRight, udevGothicOpt);
	//TextDrawer::DrawString("��hoge���I123", 1180, 132, Align::TopRight);
}
