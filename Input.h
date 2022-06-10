#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

void InitInput();

void UpdateInput();

void CloseInput();

//�L�[��������Ă��邩
bool KeyDown(int key);
//�L�[�������ꂽ�u�Ԃ�
bool KeyReleased(int key);
//�L�[�������ꂽ�u�Ԃ�
bool KeyTriggered(int key);