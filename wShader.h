#pragma once
#include "Essentials.h"
#include "wDirectX.h"
class wShader
{
public:
	void Init();

	ComPtr<ID3DBlob> vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
};

void RegisterAndInitShader(string id);
wShader* GetShader(string id);

