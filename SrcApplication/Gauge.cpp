#include "stdafx.h"
#include "Gauge.h"

Gauge::Gauge(const Vec3& pos, const Vec3& scale) :
	pos(pos), scale(scale), gaugeExrate(1)
{
	gaugeFrameSprite.reset(new Sprite("gaugeFrame"));
	gaugeFrontColorSprite.reset(new Sprite("white"));
	gaugeBackColorSprite.reset(new Sprite("white"));

	// �t���[��
	gaugeFrameSprite->position = pos;
	gaugeFrameSprite->scale = scale;

	// �O�̐F
	float xAxisMaxScale = 126 * gaugeFrameSprite->scale.x;
	gaugeFrontColorSprite->scale = Vec3(126 * gaugeExrate, 6, 0) * (Vec3)gaugeFrameSprite->scale;
	gaugeFrontColorSprite->position =
	{
		gaugeFrameSprite->position.x - (xAxisMaxScale - gaugeFrontColorSprite->scale.x) / 2,
		gaugeFrameSprite->position.y,
		gaugeFrameSprite->position.z
	};

	// ���̐F
	gaugeBackColorSprite->scale = gaugeFrontColorSprite->scale;
	gaugeBackColorSprite->position = gaugeFrontColorSprite->position;
}

void Gauge::Update()
{
	// �t���[��
	gaugeFrameSprite->position = pos;
	gaugeFrameSprite->scale = scale;

	// �O�̐F�̏���
	float xAxisMaxScale = 126 * gaugeFrameSprite->scale.x;
	gaugeFrontColorSprite->scale = Vec3(126 * gaugeExrate, 6, 0) * (Vec3)gaugeFrameSprite->scale;
	gaugeFrontColorSprite->position =
	{
		gaugeFrameSprite->position.x - (xAxisMaxScale - gaugeFrontColorSprite->scale.x) / 2,
		gaugeFrameSprite->position.y,
		gaugeFrameSprite->position.z
	};

	// ���̐F�̏���
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

	// �s��X�V
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
