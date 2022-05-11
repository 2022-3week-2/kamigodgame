#include "wDirectX.h"
#include "wSwapChainManager.h"
static wDirectX WDX;

wDirectX* GetWDX()
{
	return &WDX;
}

void InitWDX()
{
	WDX.Init();
}

void wDirectX::Init() {
	result = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
	vector< ComPtr<IDXGIAdapter1>> adapters;

	ComPtr<IDXGIAdapter1> tmpAdapter = nullptr;

	//�O���{�N�̖ʐڂ��܁`�`��
	for (int i = 0; dxgiFactory->EnumAdapters1(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; i++)
	{
		adapters.push_back(tmpAdapter);
	}

	for (auto& adp : adapters)
	{
		DXGI_ADAPTER_DESC1 adesc;
		adp->GetDesc1(&adesc);

		//�\�t�g�E�F�A�͂��ĂтłȂ��̂ł��F�胁�[��
		if (adesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
			continue;
		}

		wstring strDesc = adesc.Description;
		// Intel UHD�͂���Ȃ�
		if (strDesc.find(L"Intel") == wstring::npos)
		{
			//�N�D�G���˂��`�̗p��
			tmpAdapter = adp;
			break;
		}
	}

	//�f�o�C�X����(�����������Ȃ��悤�ɁI)
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel;

	for (int i = 0; i < _countof(levels); i++)
	{
		//�̗p�����A�_�v�^�[�Ńf�o�C�X�𐶐�
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i], IID_PPV_ARGS(&dev));
		if (result == S_OK)
		{
			featureLevel = levels[i];
			break;
		}
	}

	//�R�}���h���X�g�ƃR�}���h�L���[
	result = dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAllocator));

	result = dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator.Get(), nullptr, IID_PPV_ARGS(&cmdList));

	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc{};

	dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&cmdQueue));


}

void wDirectX::EndFrame()
{	
	//���߂����s���ĕ`��
	cmdList->Close();

	ID3D12CommandList* cmdLists[] = { cmdList.Get() };
	cmdQueue->ExecuteCommandLists(1, cmdLists);

	GetSCM()->swapchain->Present(1, 0);

	GetSCM()->WaitForRender();
}
