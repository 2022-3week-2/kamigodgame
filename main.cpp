#include "Essentials.h"
#include "wWindow.h"
#include "wDirectX.h"
#include "Input.h"

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
	struct Vertex
	{
		XMFLOAT3 pos;
		XMFLOAT2 uv;
	};

	Vertex vertices[] = {
		//�O
		{{-5, -5, -5},{0.0f, 1.0f}},
		{{-5,  5, -5},{0.0f, 0.0f}},
		{{ 5, -5, -5},{1.0f, 1.0f}},
		{{ 5,  5, -5},{1.0f, 0.0f}},

		//��
		{{-5, -5,  5},{0.0f, 1.0f}},
		{{-5,  5,  5},{0.0f, 0.0f}},
		{{ 5, -5,  5},{1.0f, 1.0f}},
		{{ 5,  5,  5},{1.0f, 0.0f}},

		//��
		{{-5, -5, -5},{0.0f, 1.0f}},
		{{-5, -5,  5},{0.0f, 0.0f}},
		{{-5,  5, -5},{1.0f, 1.0f}},
		{{-5,  5,  5},{1.0f, 0.0f}},

		//�E
		{{ 5, -5, -5},{0.0f, 1.0f}},
		{{ 5, -5,  5},{0.0f, 0.0f}},
		{{ 5,  5, -5},{1.0f, 1.0f}},
		{{ 5,  5,  5},{1.0f, 0.0f}},

		//��
		{{-5, -5, -5},{0.0f, 1.0f}},
		{{ 5, -5, -5},{0.0f, 0.0f}},
		{{-5, -5,  5},{1.0f, 1.0f}},
		{{-5, -5,  5},{1.0f, 0.0f}},

		//��
		{{-5,  5, -5},{0.0f, 1.0f}},
		{{ 5,  5, -5},{0.0f, 0.0f}},
		{{-5,  5,  5},{1.0f, 1.0f}},
		{{-5,  5,  5},{1.0f, 0.0f}},
	};

	UINT sizeVB = static_cast<UINT>(sizeof(Vertex) * _countof(vertices));

	////���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapprop{};
	heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC resdesc{};
	resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resdesc.Width = sizeVB;
	resdesc.Height = 1;
	resdesc.DepthOrArraySize = 1;
	resdesc.MipLevels = 1;
	resdesc.SampleDesc.Count = 1;
	resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	ComPtr<ID3D12Resource> vertBuff = nullptr;
	result = GetWDX()->dev->CreateCommittedResource(
		&heapprop,
		D3D12_HEAP_FLAG_NONE,
		&resdesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);

	// GPU��̃o�b�t�@�ɑΉ��������z���������擾
	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);

	// �S���_�ɑ΂���
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];   // ���W���R�s�[
	}

	// �}�b�v������
	vertBuff->Unmap(0, nullptr);

	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(Vertex);

	////���_�C���f�b�N�X
	unsigned short indices[] =
	{
		0,1,2,
		1,2,3,

		4,5,6,
		5,6,7,

		8,9,10,
		9,10,11,

		12,13,14,
		13,14,15,

		16,17,18,
		17,18,19,

		20,21,22,
		21,22,23,
	};

	//���_�C���f�b�N�X�o�b�t�@�̐���
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * _countof(indices));

	ComPtr<ID3D12Resource> indexBuff = nullptr;
	resdesc.Width = sizeIB;

	GetWDX()->dev->CreateCommittedResource(
		&heapprop,
		D3D12_HEAP_FLAG_NONE,
		&resdesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff)
	);

	// GPU��̃o�b�t�@�ɑΉ��������z���������擾
	unsigned short* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);

	// �S���_�ɑ΂���
	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];   // ���W���R�s�[
	}

	// �}�b�v������
	indexBuff->Unmap(0, nullptr);

	// ���_�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};

	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;


	////�萔�o�b�t�@
	struct ConstBufferData {
		XMFLOAT4 color;
		XMMATRIX mat;//3D�ϊ��s��
	};

	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES cbheapprop{};
	cbheapprop.Type = D3D12_HEAP_TYPE_UPLOAD;

	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC cbresdesc{};
	cbresdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbresdesc.Width = (sizeof(ConstBufferData) + 0xff) & ~0xff;
	cbresdesc.Height = 1;
	cbresdesc.DepthOrArraySize = 1;
	cbresdesc.MipLevels = 1;
	cbresdesc.SampleDesc.Count = 1;
	cbresdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//GPU���\�[�X�̐���
	ComPtr<ID3D12Resource> constBuff[3] = { nullptr , nullptr, nullptr };
	GetWDX()->dev->CreateCommittedResource(
		&cbheapprop,
		D3D12_HEAP_FLAG_NONE,
		&cbresdesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff[0]));

	GetWDX()->dev->CreateCommittedResource(
		&cbheapprop,
		D3D12_HEAP_FLAG_NONE,
		&cbresdesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff[1]));

	GetWDX()->dev->CreateCommittedResource(
		&cbheapprop,
		D3D12_HEAP_FLAG_NONE,
		&cbresdesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff[2]));

	//�萔�o�b�t�@��U�����܂�

	//�摜�f�[�^�̍쐬
	const int texWidth = 256;
	const int imageDataCount = texWidth * texWidth;

	unique_ptr<XMFLOAT4> imageData = unique_ptr<XMFLOAT4>(new XMFLOAT4[imageDataCount]);

	for (int i = 0; i < imageDataCount; i++)
	{
		imageData.get()[i].x = i % 256 < 128 ? 1.0f : 0.0f;
		imageData.get()[i].y = i % 256 < 128 ? 0.0f : 1.0f;
		imageData.get()[i].z = 0.0f;
		imageData.get()[i].w = 1.0f;
	}

	//�e�N�X�`���o�b�t�@
	D3D12_HEAP_PROPERTIES texHeapProp{};
	texHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	texHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	texHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;

	D3D12_RESOURCE_DESC texresdesc{};
	texresdesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texresdesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texresdesc.Width = texWidth;
	texresdesc.Height = texWidth;
	texresdesc.DepthOrArraySize = 1;
	texresdesc.MipLevels = 1;
	texresdesc.SampleDesc.Count = 1;

	ComPtr<ID3D12Resource> texBuff = nullptr;
	GetWDX()->dev->CreateCommittedResource(
		&texHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&texresdesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texBuff));

	texBuff->WriteToSubresource(
		0,
		nullptr,
		imageData.get(),
		sizeof(XMFLOAT4) * texWidth,
		sizeof(XMFLOAT4) * imageDataCount
	);

	//�萔�o�b�t�@�p�̃f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> basicDescHeap = nullptr;

	//�ݒ�\����
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	descHeapDesc.NumDescriptors = 4;

	//����
	GetWDX()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&basicDescHeap));

	D3D12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = basicDescHeap->GetCPUDescriptorHandleForHeapStart();


	//�萔�o�b�t�@�r���[�̍쐬
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc{};
	cbvDesc.BufferLocation = constBuff[0]->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (UINT)constBuff[0]->GetDesc().Width;
	GetWDX()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);

	basicHeapHandle.ptr += GetWDX()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc1{};
	cbvDesc.BufferLocation = constBuff[1]->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (UINT)constBuff[1]->GetDesc().Width;
	GetWDX()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);

	basicHeapHandle.ptr += GetWDX()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc2{};
	cbvDesc.BufferLocation = constBuff[2]->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (UINT)constBuff[2]->GetDesc().Width;
	GetWDX()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);

	//�萔�o�b�t�@�����܂�

	//�V�F�[�_�[���\�[�X�r���[�̐���
	basicHeapHandle.ptr += GetWDX()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	GetWDX()->dev->CreateShaderResourceView(texBuff.Get(), &srvDesc, basicHeapHandle);




	//�V�F�[�_�[�̓ǂݍ��݂ƃR���p�C��
	ComPtr<ID3DBlob> vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob = nullptr; // �G���[�I�u�W�F�N�g

	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"BasicVS.hlsl",  // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		"main", "vs_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		&vsBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"BasicPS.hlsl",   // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		"main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		&psBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// ���_���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
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


	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};

	gpipeline.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	gpipeline.VS.BytecodeLength = vsBlob->GetBufferSize();
	gpipeline.PS.pShaderBytecode = psBlob->GetBufferPointer();
	gpipeline.PS.BytecodeLength = psBlob->GetBufferSize();

	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;  // �J�����O���Ȃ�
	gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
	gpipeline.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����

	gpipeline.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;  // RBGA�S�Ẵ`�����l����`��

	gpipeline.NumRenderTargets = 1; // �`��Ώۂ�1��
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0�`255�w���RGBA
	gpipeline.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	ComPtr<ID3D12RootSignature> rootsignature;

	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<ID3DBlob> rootSigBlob = nullptr;
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	result = GetWDX()->dev->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootsignature));

	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	gpipeline.pRootSignature = rootsignature.Get();

	ComPtr<ID3D12PipelineState> pipelinestate = nullptr;
	result = GetWDX()->dev->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelinestate));
	/*Init Draw End*/

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

		//�o�b�N�o�b�t�@�ԍ����擾(0��1)
		UINT bbIndex = GetWDX()->swapchain->GetCurrentBackBufferIndex();

		//���\�[�X�o���A�[���������݉\��Ԃ�
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = GetWDX()->backBuffers[bbIndex].Get();
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		GetWDX()->cmdList->ResourceBarrier(1, &barrierDesc);

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvH = CD3DX12_CPU_DESCRIPTOR_HANDLE(GetWDX()->rtvHeaps->GetCPUDescriptorHandleForHeapStart(),
		bbIndex, GetWDX()->dev->GetDescriptorHandleIncrementSize(GetWDX()->heapDesc.Type));
		GetWDX()->cmdList->OMSetRenderTargets(1, &rtvH, false, nullptr);

		//��ʃN���A
		float clearColor[] = { 0.1f, 0.25f, 0.5f, 0.0f };
		GetWDX()->cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);

		/*�`�揈��*/
		GetWDX()->cmdList->SetPipelineState(pipelinestate.Get());
		GetWDX()->cmdList->SetGraphicsRootSignature(rootsignature.Get());

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

		GetWDX()->cmdList->IASetVertexBuffers(0, 1, &vbView);

		GetWDX()->cmdList->IASetIndexBuffer(&ibView);

		GetWDX()->cmdList->RSSetScissorRects(1, &scissorrect);

		GetWDX()->cmdList->DrawInstanced(ibView.SizeInBytes / sizeof(short), 1, 0, 0);

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