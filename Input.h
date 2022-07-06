#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace Input {

	class Key
	{
	public:
		static void Init();

		static void Update();

		static void Close();

		//�L�[��������Ă��邩
		static bool Down(int key);
		//�L�[�������ꂽ�u�Ԃ�
		static bool Released(int key);
		//�L�[�������ꂽ�u�Ԃ�
		static bool Triggered(int key);

		static Key* GetInstance();
	private:
		IDirectInput8* dinput = nullptr;
		IDirectInputDevice8* devkeyboard = nullptr;

		BYTE keys[256] = {};
		BYTE prevKeys[256] = {};
	};

	class Pad
	{

	};

}