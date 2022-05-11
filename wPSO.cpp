#include "wPSO.h"
map<string, wPSO> psoMap;

wPSO::wPSO(wShader* shader):shader(shader)
{
}

void wPSO::InitDesc()
{
	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	psod.VS.pShaderBytecode = shader->vsBlob->GetBufferPointer();
	psod.VS.BytecodeLength = shader->vsBlob->GetBufferSize();
	psod.PS.pShaderBytecode = shader->psBlob->GetBufferPointer();
	psod.PS.BytecodeLength = shader->psBlob->GetBufferSize();

	psod.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	psod.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�
	psod.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;  // �J�����O���Ȃ�
	psod.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
	psod.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����

	psod.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;  // RBGA�S�Ẵ`�����l����`��

	psod.NumRenderTargets = 1; // �`��Ώۂ�1��
	psod.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0�`255�w���RGBA
	psod.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	//Depth
	psod.DepthStencilState.DepthEnable = true;
	psod.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	psod.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	psod.DSVFormat = DXGI_FORMAT_D32_FLOAT;
}

void wPSO::Create()
{
	GetWDX()->dev->CreateGraphicsPipelineState(&psod, IID_PPV_ARGS(&pso));
}

void RegisterAndInitPSO(string id, wShader* shader) 
{
	psoMap[id] = wPSO(shader);
	psoMap[id].InitDesc();
}

D3D12_GRAPHICS_PIPELINE_STATE_DESC* GetPSODesc(string id)
{
	return &psoMap[id].psod;
}

ID3D12PipelineState* GetPSO(string id)
{
	return psoMap[id].pso.Get();
}

wPSO* GetWPSO(string id)
{
	return &psoMap[id];
}
