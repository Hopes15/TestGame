#include "Input.h"

Input::Input(HWND hwnd)
{
	//������
	memset(&mKeys, 0, sizeof(mKeys));

	//DirectInput���쐬
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
		std::cout << "DirectInput�̐����Ɏ��s���܂���" << std::endl;
#endif
		return;
	}

	//Divice(Key)���쐬
	result = pInput->CreateDevice(
		/*GUID				  */ GUID_SysKeyboard,
		/*LPDIRECTINPUTDEVICE8*/ &pDevice,
		/*LPUNKNOWN			  */ NULL
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "Device�̐����Ɏ��s���܂���" << std::endl;
#endif
		return;
	}

	//Device��Format
	result = pDevice->SetDataFormat(&c_dfDIKeyboard);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "Device��Format�Ɏ��s���܂���" << std::endl;
#endif
		return;
	}

	//Device�̐ݒ�
	result = pDevice->SetCooperativeLevel(
		hwnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "Device�̐ݒ�Ɏ��s���܂���" << std::endl;
#endif
		return;
	}

	//���͎�t
	pDevice->Acquire();
}

bool Input::GetKey(UINT KeyCode)
{
	// �L�[�{�[�h��Ԃ̎擾
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
