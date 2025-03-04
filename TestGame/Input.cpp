#include "Input.h"

Input::Input(HWND hwnd)
{
	//初期化
	memset(&mKeys, 0, sizeof(mKeys));

	//DirectInputを作成
	auto result = DirectInput8Create(
		/*HINSTANCE*/ GetModuleHandle(0),
		/*Version  */ DIRECTINPUT_VERSION,
		/*IID	   */ IID_IDirectInput8,
		/*ppvOut   */ (void**)&pInput,
		/*punkOuter*/ NULL
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "DirectInputの生成に失敗しました" << std::endl;
#endif
		return;
	}

	//Divice(Key)を作成
	result = pInput->CreateDevice(
		/*GUID				  */ GUID_SysKeyboard,
		/*LPDIRECTINPUTDEVICE8*/ &pDevice,
		/*LPUNKNOWN			  */ NULL
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "Deviceの生成に失敗しました" << std::endl;
#endif
		return;
	}

	//DeviceをFormat
	result = pDevice->SetDataFormat(&c_dfDIKeyboard);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "DeviceのFormatに失敗しました" << std::endl;
#endif
		return;
	}

	//Deviceの設定
	result = pDevice->SetCooperativeLevel(
		hwnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "Deviceの設定に失敗しました" << std::endl;
#endif
		return;
	}

	//入力受付
	pDevice->Acquire();
}

bool Input::GetKey(UINT KeyCode)
{
	// キーボード状態の取得
	pDevice->GetDeviceState(sizeof(mKeys), (LPVOID)&mKeys);

	if (mKeys[KeyCode] & 0x80) return true;
	else					   return false;
}

Input::~Input()
{
	pDevice->Unacquire();
	pDevice->Release();
	pInput ->Release();
}
