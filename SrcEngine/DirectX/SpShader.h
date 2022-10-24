#pragma once
#include "Essentials.h"
#include "SpDirectX.h"
class SpShader
{
public:
	void Init(string vsPath, string psPath);

	ComPtr<ID3DBlob> vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
};

void RegisterAndInitShader(string id, string vsPath, string psPath);
SpShader* GetShader(string id);

