#include "Essentials.h"
#include "wWindow.h"
#include "wDirectX.h"
#include "Input.h"
#include "wSwapChainManager.h"
#include "wDepth.h"
#include "wShader.h"
#include "wPSO.h"
#include "wTexture.h"
#include "Vec3.h"
#include "wConstBuffer.h"
#include "Object3D.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	/*�f�o�b�O�L����*/
#ifdef  _DEBUG
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
#endif //  _DEBUG

	//�E�B���h�E�𐶐�
	{
		wWindow wwnd;
		wwnd.Create(L"DirectXTest", 1280, 720);
		RegisterwWindow(wwnd, "Default");
	}

	MSG msg{};

	/*DirectX����������*/
	InitWDX();
	HRESULT result;

	//Init Input
	InitInput();

	/*Init Draw*/
	//�_�u���o�b�t�@�����O�Ƃ�
	InitWSCM();
	InitWDepth();

	////�萔�o�b�t�@
	struct ConstBufferDataMaterial {
		XMFLOAT4 color; //RGBA
	};

	wConstBuffer<ConstBufferDataMaterial> materialCB;

	//Objects
	Model model;

	list<Object3D> objects;

	for (int i = 0; i < 1; i++)
	{
		objects.push_back(Object3D());
	}

	for (auto itr = objects.begin(); itr != objects.end(); itr++)
	{
		itr->model = &model;
	}

	//�萔�o�b�t�@�����܂�

	// ���_���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
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

	//PSO
	InitTextureBuff();
	RegisterAndInitShader("def");
	RegisterAndInitPSO("def", GetShader("def"));

	GetPSODesc("def")->InputLayout.pInputElementDescs = inputLayout;
	GetPSODesc("def")->InputLayout.NumElements = _countof(inputLayout);

	D3D12_DESCRIPTOR_RANGE descRange{};
	descRange.NumDescriptors = 1;
	descRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descRange.BaseShaderRegister = 0;
	descRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	D3D12_ROOT_PARAMETER rootParams[3] = {};

	//�萔�o�b�t�@0��
	rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParams[0].Descriptor.ShaderRegister = 0;
	rootParams[0].Descriptor.RegisterSpace = 0;
	rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	//�e�N�X�`�����W�X�^0��
	rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParams[1].DescriptorTable.pDescriptorRanges = &descRange;
	rootParams[1].DescriptorTable.NumDescriptorRanges = 1;
	rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	//�萔�o�b�t�@1��
	rootParams[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParams[2].Descriptor.ShaderRegister = 1;
	rootParams[2].Descriptor.RegisterSpace = 0;
	rootParams[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	ComPtr<ID3D12RootSignature> rootsignature;

	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams;
	rootSignatureDesc.NumParameters = _countof(rootParams);

	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	rootSignatureDesc.pStaticSamplers = &samplerDesc;
	rootSignatureDesc.NumStaticSamplers = 1;

	ComPtr<ID3DBlob> rootSigBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	result = GetWDX()->dev->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootsignature));

	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	GetPSODesc("def")->pRootSignature = rootsignature.Get();
	GetWPSO("def")->Create();
	/*Init Draw End*/
	XMMATRIX wMat = XMMatrixIdentity();
	/*���[�v*/
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			break;
		}

		/*���t���[������*/
		/*�X�V����*/


		/*�X�V���������܂�*/


		/*�`�揈��*/
		//�ϊ�
		XMMATRIX pMat = XMMatrixPerspectiveFovLH(
			XMConvertToRadians(45.0f),
			(float)GetwWindow()->width / GetwWindow()->height,
			0.1f, 1000.0f
		);

		XMMATRIX vMat;
		XMFLOAT3 eye(0, 0, -300);
		XMFLOAT3 target(0, 0, 0);
		XMFLOAT3 up(0, 1, 0);

		vMat = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

		objects.begin()->rotation.x += 0.01;
		objects.begin()->UpdateMatrix();

		XMMATRIX vproj = vMat * pMat;
		/*�`�揈�������܂�*/

		//�o�b�N�o�b�t�@�ԍ����擾(0��1)
		UINT bbIndex = GetSCM()->swapchain->GetCurrentBackBufferIndex();

		//���\�[�X�o���A�[���������݉\��Ԃ�
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = GetSCM()->backBuffers[bbIndex].Get();
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		GetWDX()->cmdList->ResourceBarrier(1, &barrierDesc);

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(GetSCM()->rtvHeaps->GetCPUDescriptorHandleForHeapStart(),
		bbIndex, GetWDX()->dev->GetDescriptorHandleIncrementSize(GetSCM()->heapDesc.Type));
		D3D12_CPU_DESCRIPTOR_HANDLE dsvH = GetWDepth()->dsvHeap->GetCPUDescriptorHandleForHeapStart();
		GetWDX()->cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);

		//��ʃN���A
		float clearColor[] = { 0.1f, 0.25f, 0.5f, 0.0f };
		GetWDX()->cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
		GetWDX()->cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH,1.0, 0, 0, nullptr);

		/*�`�揈��*/
		GetWDX()->cmdList->SetPipelineState(GetPSO("def"));
		GetWDX()->cmdList->SetGraphicsRootSignature(rootsignature.Get());

		//ID3D12DescriptorHeap* ppHeaps[] = { basicDescHeap.Get()};
		//GetWDX()->cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
		//GetWDX()->cmdList->SetGraphicsRootDescriptorTable(0, basicDescHeap->GetGPUDescriptorHandleForHeapStart());

		GetWDX()->cmdList->SetGraphicsRootConstantBufferView(0, materialCB.buffer->GetGPUVirtualAddress());

		ID3D12DescriptorHeap* ppSrvHeap[] = {GetShader("def")->srvHeap.Get()};
		GetWDX()->cmdList->SetDescriptorHeaps(1, ppSrvHeap);
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = GetShader("def")->srvHeap->GetGPUDescriptorHandleForHeapStart();
		GetWDX()->cmdList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);

		D3D12_VIEWPORT viewport{};

		viewport.Width = GetwWindow()->width;
		viewport.Height = GetwWindow()->height;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		GetWDX()->cmdList->RSSetViewports(1, &viewport);

		D3D12_RECT scissorrect{};

		scissorrect.left = 0;                                       // �؂蔲�����W��
		scissorrect.right = scissorrect.left + GetwWindow()->width;        // �؂蔲�����W�E
		scissorrect.top = 0;                                        // �؂蔲�����W��
		scissorrect.bottom = scissorrect.top + GetwWindow()->height;       // �؂蔲�����W��

		GetWDX()->cmdList->RSSetScissorRects(1, &scissorrect);

		GetWDX()->cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		GetWDX()->cmdList->RSSetScissorRects(1, &scissorrect);

		for (auto itr = objects.begin(); itr != objects.end(); itr++)
		{
			itr->Draw(vproj);
		}

		/*�`�揈�������܂�*/

		//���\�[�X�o���A�[��߂�
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

		GetWDX()->cmdList->ResourceBarrier(1, &barrierDesc);

		/*���t���[�����������܂�*/
		GetWDX()->EndFrame();
	}
	/*���[�v�����܂�*/
	CloseAllwWindow();


	return 0;
}