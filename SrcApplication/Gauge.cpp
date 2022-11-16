#include "stdafx.h"
#include "Gauge.h"

Gauge::Gauge(const Vec3& pos, const Vec3& scale, const TextureKey& frameTex) :
	pos(pos), scale(scale), gaugeExrate(1)
{
	gaugeFrameSprite.reset(new Sprite(frameTex));
	gaugeFrontColorSprite.reset(new Sprite("white"));
	gaugeBackColorSprite.reset(new Sprite("white"));

	// フレーム
	gaugeFrameSprite->position = pos;
	gaugeFrameSprite->scale = scale;

	// 前の色
	colorWidth = (gaugeFrameSprite->width - 2);
	xAxisMaxScale = colorWidth * gaugeFrameSprite->scale.x;
	gaugeFrontColorSprite->scale = Vec3(colorWidth * gaugeExrate, 6, 0) * (Vec3)gaugeFrameSprite->scale;
	gaugeFrontColorSprite->position =
	{
		gaugeFrameSprite->position.x - (xAxisMaxScale - gaugeFrontColorSprite->scale.x) / 2,
		gaugeFrameSprite->position.y,
		gaugeFrameSprite->position.z
	};

	// 後ろの色
	gaugeBackColorSprite->scale = gaugeFrontColorSprite->scale;
	gaugeBackColorSprite->position = gaugeFrontColorSprite->position;

	subEase.SetEaseTimer(60);
	subEase.SetPowNum(2);
	isGetEaseTarget = false;
	easeTargetPos = 0;
	easeTargetScale = 0;
	easeStartPos = 0;
	easeStartScale = 0;

}

void Gauge::Update()
{
	// フレーム
	gaugeFrameSprite->position = pos;
	gaugeFrameSprite->scale = scale;

	// 前の色の処理
	if (gaugeExrate >= 0)
	{
		colorWidth = (gaugeFrameSprite->width - 2);
		xAxisMaxScale = colorWidth * gaugeFrameSprite->scale.x;
		gaugeFrontColorSprite->scale = Vec3(colorWidth * gaugeExrate, 6, 0) * (Vec3)gaugeFrameSprite->scale;
		gaugeFrontColorSprite->position =
		{
			gaugeFrameSprite->position.x - (xAxisMaxScale - gaugeFrontColorSprite->scale.x) / 2,
			gaugeFrameSprite->position.y,
			gaugeFrameSprite->position.z
		};
		// 後ろの色の処理
		if (isGetEaseTarget == false)
		{
			if (gaugeBackColorSprite->scale.x > gaugeFrontColorSprite->scale.x)
			{
				isGetEaseTarget = true;
				easeTargetScale = gaugeFrontColorSprite->scale.x;
				easeTargetPos = gaugeFrontColorSprite->position.x;
				easeStartScale = gaugeBackColorSprite->scale.x;
				easeStartPos = gaugeBackColorSprite->position.x;
			}
		}
		else if (isGetEaseTarget == true)
		{
			subEase.Update();
			gaugeBackColorSprite->scale.x = subEase.Out(easeStartScale, easeTargetScale);
			gaugeBackColorSprite->position.x = subEase.Out(easeStartPos, easeTargetPos);
			if (subEase.GetisEnd() == true)
			{
				subEase.ReSet();
				gaugeBackColorSprite->scale.x = gaugeFrontColorSprite->scale.x;
				gaugeBackColorSprite->position.x = gaugeFrontColorSprite->position.x;
				isGetEaseTarget = false;
			}
		}
		gaugeBackColorSprite->position.y = gaugeFrameSprite->position.y;
	}

	// 行列更新
	gaugeFrameSprite->UpdateMatrix();
	gaugeFrontColorSprite->UpdateMatrix();
	gaugeBackColorSprite->UpdateMatrix();
}

void Gauge::DrawFrontSprite()
{
	gaugeBackColorSprite->Draw();
	gaugeFrontColorSprite->Draw();
	gaugeFrameSprite->Draw();
}
