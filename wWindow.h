#pragma once
#include "Essentials.h"


class wWindow
{
public:
	void Create(LPCWSTR title, int windowWidth, int windowHeight);
	void Close();

	HWND hwnd;
	WNDCLASSEX  w{};

	int width = 1280;
	int height = 720;
private:
};

/// <summary>
///	wWindow���X�g����w��ID��wWindow��T���ĕԂ��B
/// ID���w�肵�Ȃ��ꍇ��SetDefaultWindowID�Ŏw�肵��ID���g���B
/// </summary>
/// <param name="ID">string�^��ID</param>
/// <returns>����:wWindow�ւ̃|�C���^,���s:nullptr</returns>
wWindow* GetwWindow(string ID);
wWindow* GetwWindow();
extern map<string, wWindow> wWindowList;
void RegisterwWindow(wWindow wwnd, string ID);
void SetDefaultWindowID(string ID);

void CloseAllwWindow();
