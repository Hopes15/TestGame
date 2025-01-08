#include "Window.h"

LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void Window::SetUpWindow(const LONG WINDOW_WIDTH, const LONG WINDOW_HEIGHT, LPCWSTR APP_NAME)
{
	//�E�B���h�E�N���X�̒�`
	mWndClass.cbSize = sizeof(WNDCLASSEX);
	mWndClass.lpfnWndProc = (WNDPROC)WindowProcedure;
	mWndClass.lpszClassName = _T("GameEngine");
	mWndClass.hInstance = GetModuleHandle(nullptr);

	RegisterClassEx(&mWndClass);

	//�T�C�Y����
	RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�I�u�W�F�N�g�̐���
	mHwnd = CreateWindow(
		mWndClass.lpszClassName,
		APP_NAME,
		WS_OVERLAPPED | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr,
		nullptr,
		mWndClass.hInstance,
		nullptr
	);

	//�E�B���h�E��\��
	ShowWindow(mHwnd, SW_SHOW);
}

bool Window::GetMSG()
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.message != WM_QUIT;
}

void Window::QuitApp()
{
	//�o�^����
	UnregisterClass(mWndClass.lpszClassName, mWndClass.hInstance);
}

const HWND& Window::GetWindowHandler()
{
	return mHwnd;
}
