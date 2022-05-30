#pragma once
#include "Essentials.h"
#include "wWindow.h"

struct ConstBufferDataMaterial {
	Float4 color; //RGBA
};

class wDirectX
{
public:
	void Init();

	bool StartFrame();

	void PreDrawCommands();

	void PostDrawCommands();

	void EndFrame();

	HRESULT result;
	ComPtr<ID3D12Device> dev = nullptr;
	ComPtr<IDXGIFactory6> dxgiFactory = nullptr;
	ComPtr<ID3D12CommandAllocator> cmdAllocator = nullptr;
	ComPtr<ID3D12GraphicsCommandList> cmdList = nullptr;
	ComPtr<ID3D12CommandQueue> cmdQueue = nullptr;

	D3D12_RESOURCE_BARRIER barrierDesc{};

	MSG msg{};

private:
};

wDirectX* GetWDX();
void InitWDX();

