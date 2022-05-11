#pragma once
#include "Essentials.h"
#include "wShader.h"
//TODO:設計がガバすぎるのでpso,shader,rootsignature,textureの設計を見直す
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



