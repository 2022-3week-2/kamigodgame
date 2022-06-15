#pragma once
#include "Essentials.h"
#include "wDirectX.h"
#include "Vec3.h"
//TODO:���_�f�[�^��ǂݍ��߂�悤�ɂ���

struct Vertex
{
	Float3 pos;
	Float3 normal;
	Float2 uv;
};

struct Material
{
	std::string name;
	Float3 ambient;
	Float3 diffuse;
	Float3 specular;
	float alpha;
	std::string textureFile;

	Material() {
		ambient = {0.3, 0.3, 0.3};
		diffuse = {0.0f, 0.0f, 0.0f};
		specular = {0.0f, 0.0f, 0.0f};
		alpha = 1.0f;
	}
};

// ���_���C�A�E�g
static D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},

		{
			"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},

		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}
};

class Model
{
public:
	Model();
	Model(string path);

	D3D12_VERTEX_BUFFER_VIEW vbView{};
	D3D12_INDEX_BUFFER_VIEW ibView{};

	ComPtr<ID3D12Resource> vertBuff = nullptr;
	ComPtr<ID3D12Resource> indexBuff = nullptr;

	Material material;
};