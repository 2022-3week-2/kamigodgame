#pragma once
#include "Essentials.h"
//TODO:�������傢���Ƃ�����
class wTexture
{
public:
	//����������init
	void LoadTexture(string path);

	ComPtr<ID3D12Resource> texBuff = nullptr;
	D3D12_RESOURCE_DESC texresdesc{};
};

void InitTextureBuff();
wTexture* GetTexture();
