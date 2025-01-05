#pragma once
#ifdef _DEBUG
#include <iostream>
#endif

#include <vector>
//DirectX12
#include <d3d12.h>
#include <d3dx12.h>
#pragma comment (lib, "d3d12.lib")
//DXGI
#include <dxgi1_6.h>
#pragma comment(lib, "dxgi.lib")

#include <wrl.h>
using namespace Microsoft::WRL;

#include "DescriptorHeap.h"

class DX12
{
	//�V���O���g��
public:
	/// <summary>
	/// DX12�N���X�̃C���X�^���X���擾
	/// </summary>
	/// <returns>pInstance (DX12*)</returns>
	static DX12* GetInstance() 
	{
		return pInstance; 
	}
	
	/// <summary>
	/// DX12�N���X��������
	/// </summary>
	/// <param name="WIDTH">Window�̕�</param>
	/// <param name="HEIGHT">Window�̍���</param>
	/// <param name="hwnd">WindowHandler�̃C���X�^���X</param>
	static void Create(UINT WIDTH, UINT HEIGHT, HWND hwnd)
	{
		if (!pInstance) pInstance = new DX12(WIDTH, HEIGHT, hwnd); 
	}

	/// <summary>
	/// DX12�N���X�̃C���X�^���X��j��
	/// </summary>
	static void Destroy()
	{
		delete pInstance;
		pInstance = nullptr;
	}
	
private:
	static DX12* pInstance;

	DX12(UINT WIDTH, UINT HEIGHT, HWND hwnd);
	~DX12();

public:
	/// <summary>
	/// �`�揀������
	/// </summary>
	void EnterDrawing();

	/// <summary>
	/// �`��I������
	/// </summary>
	void ExitDrawing();

	/// <summary>
	/// �f�o�C�X�N���X�̃|�C���^�[��Ԃ�
	/// </summary>
	/// <returns>ID3D12Device*</returns>
	inline ID3D12Device* GetDevice(){ return mDevice.Get(); }

	/// <summary>
	/// �R�}���h���X�g�̃|�C���^�[��Ԃ�
	/// </summary>
	/// <returns>ID3D12GraphicsCommandList*</returns>
	inline ID3D12GraphicsCommandList* GetCmdList() { return mCmdList.Get(); }

	/// <summary>
	/// �X���b�v�`�F�[���S�̃|�C���^�[��Ԃ�
	/// </summary>
	/// <returns>IDXGISwapChain4*</returns>
	inline IDXGISwapChain4* GetSwapChain4() { return mSwapChain4.Get(); }

private:
	//Create�֐�
	bool CreateFactory();
	bool CreateDevice();
	bool CreateCmdAllocator();
	bool CreateCmdList();
	bool CreateCmdQueue();
	bool CreateSwapChain();
	bool CreateFence();

	//Draw�֘A
	void WaitDrawing();
	
public:
	const UINT WINDOW_WIDTH;
	const UINT WINDOW_HEIGHT;
	const UINT BUFFER_COUNT;

private:
	UINT64 mFenceVal;
	HWND   mHWND = {};
	 
	ComPtr<IDXGIFactory6>				mFactory	  = nullptr;
	ComPtr<IDXGIAdapter>				mAdapter	  = nullptr;
	ComPtr<ID3D12Device>				mDevice		  = nullptr;
	ComPtr<ID3D12CommandAllocator>		mCmdAllocator = nullptr;
	ComPtr<ID3D12GraphicsCommandList>	mCmdList	  = nullptr;
	ComPtr<ID3D12CommandQueue>		    mCmdQueue	  = nullptr;
	ComPtr<IDXGISwapChain4>			    mSwapChain4	  = nullptr;
	ComPtr<ID3D12Fence>					mFence		  = nullptr;

};

