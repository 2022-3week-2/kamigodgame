#pragma once
#include "Essentials.h"

class SpRootSignature
{
public:
	void Create();
	void UseDefaultSettings();

	ComPtr<ID3D12RootSignature> rootsignature;
	vector<CD3DX12_ROOT_PARAMETER> params;
	D3D12_STATIC_SAMPLER_DESC samplerDesc;

public:
	static SpRootSignature* Get(string id);
	static SpRootSignature* Register(string id);
	static map<string, SpRootSignature> rsMap;
};