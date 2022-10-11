#include "SpWindow.h"

static string defWndID = "Default";
map<string, SpWindow> wWindowList;
SpWindow* GetwWindow(string ID)
{
    auto res = wWindowList.find(ID);
    return res != wWindowList.end() ? &res->second : nullptr;
}

SpWindow* GetwWindow()
{
    return GetwWindow(defWndID);
}

void RegisterwWindow(SpWindow wwnd, string ID)
{
    wWindowList[ID] = wwnd;
}

void SetDefaultWindowID(string ID)
{
    defWndID = ID;
}

void CloseAllwWindow()
{
	for (auto itr = wWindowList.begin(); itr != wWindowList.end(); itr++)
	{
		itr->second.Close();
	}
}

void SpWindow::Create(LPCWSTR title, int windowWidth, int windowHeight) {
	width = windowWidth;
	height = windowHeight;

	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;
	w.lpszClassName = title;
	w.hInstance = GetModuleHandle(nullptr);
	w.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&w);

	//�E�B���h�E�T�C�Y��RECT
	RECT wrc = { 0, 0, width, height };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);//�T�C�Y�␳��������

	hwnd = CreateWindow(w.lpszClassName,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr, //�e�E�B���h�E�n���h��
		nullptr, //���j���[�n���h��
		w.hInstance,
		nullptr);

	ShowWindow(hwnd, SW_SHOW);
}

void SpWindow::Close()
{
	UnregisterClass(w.lpszClassName, w.hInstance);
}

bool SpWindow::ProcessMessage()
{
	MSG msg{};

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT)
	{
		return true;
	}

	return false;
}
