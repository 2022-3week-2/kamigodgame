#pragma once
#include <Object3D.h>
#include <Sprite.h>

class Gauge
{
private:
	std::unique_ptr<Sprite> gaugeFrameSprite;
	std::unique_ptr<Sprite> gaugeFrontColorSprite;
	std::unique_ptr<Sprite> gaugeBackColorSprite;

	Vec3 pos;
	Vec3 scale;
	float gaugeExrate;

public:
	Gauge(const Vec3& pos, const Vec3& scale);
	void Update();
	void DrawFrontSprite();

public:
	// セッター
	inline void SetPosition(const Vec3& pos) { this->pos = pos; }
	inline void SetScale(const Vec3& scale) { this->scale = scale; }
	inline void SetGaugeExrate(const float& gaugeExrate) { this->gaugeExrate = gaugeExrate; }
	inline void SetGaugeFrontColor(const Vec3& gaugeFrontColor)
	{
		gaugeFrontColorSprite->brightness =
		{
			gaugeFrontColor.x / 255,
			gaugeFrontColor.y / 255,
			gaugeFrontColor.z / 255,
			1.0f,
		};
	}
	inline void SetGaugeBackColor(const Vec3& gaugeBackColor)
	{
		gaugeBackColorSprite->brightness =
		{
			gaugeBackColor.x / 255,
			gaugeBackColor.y / 255,
			gaugeBackColor.z / 255,
			1.0f,
		};
	}
};

