#pragma once
#include "Essentials.h"
#include "SpTextureManager.h"
#include "SpConstBuffer.h"
class Sprite
{
public:
	struct Vertex
	{
		Float3 pos;
		Float2 uv;
	};

	struct SpriteCBuffData {
		Float4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		Matrix mat;
	};

public:
	Sprite() {};
	//既存のテクスチャを使って生成
	Sprite(TextureKey key);
	//テクスチャを読み込んでキーに保存、それを使ってSpriteを生成
	Sprite(string path, TextureKey newKey);

	static void PreSpriteDraw();
	static void PostSpriteDraw();

	void UpdateMatrix();

	void Draw();

	D3D12_VERTEX_BUFFER_VIEW vbView{};

	ComPtr<ID3D12Resource> vertBuff = nullptr;

	SpConstBuffer<SpriteCBuffData> constBuff;

	TextureKey tex;

	Float4 brightness = { 1.0f, 1.0f, 1.0f, 1.0f };

	float width;
	float height;

	float rot = 0.0f;
	Float3 position = {};
	Float3 scale = {1.0f, 1.0f, 1.0f};
	Matrix world;

	static Matrix proj;
	static void InitCommon();
};

namespace SpriteCommon {
	// 頂点レイアウト
	static D3D12_INPUT_ELEMENT_DESC inputLayout2D[] = {
			{
				"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
				D3D12_APPEND_ALIGNED_ELEMENT,
				D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
			},
			{
				"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
				D3D12_APPEND_ALIGNED_ELEMENT,
				D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
			}
	};
}