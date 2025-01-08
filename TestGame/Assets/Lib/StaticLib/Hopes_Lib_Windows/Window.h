#pragma once
#include <tchar.h>
#include <Windows.h>

class Window
{
public:
	/// <summary>
	/// �A�v���P�[�V�����X�^�[�g
	/// </summary>
	/// <param name="WINDOW_WIDTH">�E�B���h�E�̕�</param>
	/// <param name="WINDOW_HEIGHT">�E�B���h�E�̍���</param>
	/// <param name="APP_NAME">�A�v���P�[�V�����̖��O</param>
	void SetUpWindow(const LONG WINDOW_WIDTH, const LONG WINDOW_HEIGHT, LPCWSTR APP_NAME);

	/// <summary>
	/// �Q�[�����[�v���J�n���A�I�����b�Z�[�W��������False��Ԃ�
	/// </summary>
	bool GetMSG();

	/// <summary>
	/// �A�v���P�[�V�������I��
	/// </summary>
	void QuitApp();

	/// <summary>
	/// HWND��Ԃ�
	/// </summary>
	/// <returns>HWND mHwnd�̎Q��</returns>
	const HWND& GetWindowHandler();

private:
	WNDCLASSEX mWndClass = {};
	HWND	   mHwnd	 = {};
	MSG		   msg		 = {};
};

