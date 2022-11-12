#include "stdafx.h"
#include "Gauge.h"

Gauge::Gauge(const Vec3& pos, const Vec3& scale) :
	pos(pos), scale(scale), gaugeExrate(1)
{
	gaugeFrameSprite.reset(new Sprite("gaugeFrame"));
	gaugeFrontColorSprite.reset(new Sprite("white"));
	gaugeBackColorSprite.reset(new Sprite("white"));

	// フレーム
	gaugeFrameSprite->position = pos;
	gaugeFrameSprite->scale = scale;

	// 前の色
	float xAxisMaxScale = 126 * gaugeFrameSprite->scale.x;
	gaugeFrontColorSprite->scale = Vec3(126 * gaugeExrate, 6, 0) * (Vec3)gaugeFrameSprite->scale;
	gaugeFrontColorSprite->position =
	{
		gaugeFrameSprite->position.x - (xAxisMaxScale - gaugeFrontColorSprite->scale.x) / 2,
		gaugeFrameSprite->position.y,
		gaugeFrameSprite->position.z
	};

	// 後ろの色
	gaugeBackColorSprite->scale = gaugeFrontColorSprite->scale;
	gaugeBackColorSprite->position = gaugeFrontColorSprite->position;
}

void Gauge::Update()
{
	// フレーム
	gaugeFrameSprite->position = pos;
	gaugeFrameSprite->scale = scale;

	// 前の色の処理
	float xAxisMaxScale = 126 * gaugeFrameSprite->scale.x;
	gaugeFrontColorSprite->scale = Vec3(126 * gaugeExrate, 6, 0) * (Vec3)gaugeFrameSprite->scale;
	gaugeFrontColorSprite->position =
	{
		gaugeFrameSprite->position.x - (xAxisMaxScale - gaugeFrontColorSprite->scale.x) / 2,
		gaugeFrameSprite->position.y,
		gaugeFrameSprite->position.z
	};

	// 後ろの色の処理
	if (gaugeBackColorSprite->scale.x >= gaugeFrontColorSprite->scale.x)
	{
		const float subParam = 0.5f;
		gaugeBackColorSprite->scale.x -= subParam;
		gaugeBackColorSprite->position.x -= subParam / 2;
	}
	if (gaugeBackColorSprite->scale.x <= gaugeFrontColorSprite->scale.x)
	{
		gaugeBackColorSprite->scale.x = gaugeFrontColorSprite->scale.x;
		gaugeBackColorSprite->position.x = gaugeFrontColorSprite->position.x;
	}
	gaugeBackColorSprite->position.y = gaugeFrameSprite->position.y;

	// 行列更新
	gaugeFrameSprite->UpdateMatrix();
	gaugeFrontColorSprite->UpdateMatrix();
	gaugeBackColorSprite->UpdateMatrix();
}

void Gauge::DrawFrontSprite()
{
	gaugeFrameSprite->Draw();
	gaugeBackColorSprite->Draw();
	gaugeFrontColorSprite->Draw();
}
