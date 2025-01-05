#include "Input.h"

Input::Input(HWND hwnd)
{
	//èâä˙âª
	memset(&mKeys, 0, sizeof(mKeys));

	//DirectInputÇçÏê¨
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
		std::cout << "DirectInputÇÃê∂ê¨Ç…é∏îsÇµÇ‹ÇµÇΩ" << std::endl;
#endif
		return;
	}

	//Divice(Key)ÇçÏê¨
	result = pInput->CreateDevice(
		/*GUID				  */ GUID_SysKeyboard,
		/*LPDIRECTINPUTDEVICE8*/ &pDevice,
		/*LPUNKNOWN			  */ NULL
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "DeviceÇÃê∂ê¨Ç…é∏îsÇµÇ‹ÇµÇΩ" << std::endl;
#endif
		return;
	}

	//DeviceÇFormat
	result = pDevice->SetDataFormat(&c_dfDIKeyboard);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "DeviceÇÃFormatÇ…é∏îsÇµÇ‹ÇµÇΩ" << std::endl;
#endif
		return;
	}

	//DeviceÇÃê›íË
	result = pDevice->SetCooperativeLevel(
		hwnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "DeviceÇÃê›íËÇ…é∏îsÇµÇ‹ÇµÇΩ" << std::endl;
#endif
		return;
	}

	//ì¸óÕéÛït
	pDevice->Acquire();
}

bool Input::GetKey(UINT KeyCode)
{
	// ÉLÅ[É{Å[ÉhèÛë‘ÇÃéÊìæ
	pDevice->GetDeviceState(sizeof(mKeys), (LPVOID)&mKeys);

	if (mKeys[KeyCode] & 0x80) return true;
	else					   return false;
}

Input::~Input()
{
	pDevice->Unacquire();
	pDevice->Release();
	pInput->Release();
}
