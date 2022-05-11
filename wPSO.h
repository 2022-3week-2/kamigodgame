#pragma once
#include "Essentials.h"
#include "wShader.h"
//TODO:�݌v���K�o������̂�pso,shader,rootsignature,texture�̐݌v��������
class wPSO
{
public:
	wPSO() {};
	wPSO(wShader* shader);
	void InitDesc();
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psod{};
	wShader* shader; 
	ComPtr<ID3D12PipelineState> pso = nullptr;
	void Create();
};

void RegisterAndInitPSO(string id, wShader* shader);
D3D12_GRAPHICS_PIPELINE_STATE_DESC* GetPSODesc(string id);
ID3D12PipelineState* GetPSO(string id);
wPSO* GetWPSO(string id);



