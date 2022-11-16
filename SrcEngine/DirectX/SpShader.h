#pragma once
#include "Essentials.h"
#include "SpDirectX.h"
class SpShader
{
public:
	void InitVS(string vsPath);
	void InitPS(string psPath);
	void InitGS(string gsPath);

	ComPtr<ID3DBlob> vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> gsBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
};

void RegisterShader(string id);
void InitVS(string id, string vsPath);
void InitPS(string id, string psPath);
void InitGS(string id, string gsPath);
SpShader* GetShader(string id);

