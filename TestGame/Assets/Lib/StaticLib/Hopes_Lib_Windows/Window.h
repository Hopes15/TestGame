#pragma once
#include <tchar.h>
#include <Windows.h>

class Window
{
public:
	/// <summary>
	/// アプリケーションスタート
	/// </summary>
	/// <param name="WINDOW_WIDTH">ウィンドウの幅</param>
	/// <param name="WINDOW_HEIGHT">ウィンドウの高さ</param>
	/// <param name="APP_NAME">アプリケーションの名前</param>
	void SetUpWindow(const LONG WINDOW_WIDTH, const LONG WINDOW_HEIGHT, LPCWSTR APP_NAME);

	/// <summary>
	/// ゲームループを開始し、終了メッセージが来たらFalseを返す
	/// </summary>
	bool GetMSG();

	/// <summary>
	/// アプリケーションを終了
	/// </summary>
	void QuitApp();

	/// <summary>
	/// HWNDを返す
	/// </summary>
	/// <returns>HWND mHwndの参照</returns>
	const HWND& GetWindowHandler();

private:
	WNDCLASSEX mWndClass = {};
	HWND	   mHwnd	 = {};
	MSG		   msg		 = {};
};

