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
	//シングルトン
public:
	/// <summary>
	/// DX12クラスのインスタンスを取得
	/// </summary>
	/// <returns>pInstance (DX12*)</returns>
	static DX12* GetInstance() 
	{
		return pInstance; 
	}
	
	/// <summary>
	/// DX12クラスを初期化
	/// </summary>
	/// <param name="WIDTH">Windowの幅</param>
	/// <param name="HEIGHT">Windowの高さ</param>
	/// <param name="hwnd">WindowHandlerのインスタンス</param>
	static void Create(UINT WIDTH, UINT HEIGHT, HWND hwnd)
	{
		if (!pInstance) pInstance = new DX12(WIDTH, HEIGHT, hwnd); 
	}

	/// <summary>
	/// DX12クラスのインスタンスを破棄
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
	/// 描画準備処理
	/// </summary>
	void EnterDrawing();

	/// <summary>
	/// 描画終了処理
	/// </summary>
	void ExitDrawing();

	/// <summary>
	/// デバイスクラスのポインターを返す
	/// </summary>
	/// <returns>ID3D12Device*</returns>
	inline ID3D12Device* GetDevice(){ return mDevice.Get(); }

	/// <summary>
	/// コマンドリストのポインターを返す
	/// </summary>
	/// <returns>ID3D12GraphicsCommandList*</returns>
	inline ID3D12GraphicsCommandList* GetCmdList() { return mCmdList.Get(); }

	/// <summary>
	/// スワップチェーン４のポインターを返す
	/// </summary>
	/// <returns>IDXGISwapChain4*</returns>
	inline IDXGISwapChain4* GetSwapChain4() { return mSwapChain4.Get(); }

private:
	//Create関数
	bool CreateFactory();
	bool CreateDevice();
	bool CreateCmdAllocator();
	bool CreateCmdList();
	bool CreateCmdQueue();
	bool CreateSwapChain();
	bool CreateFence();

	//Draw関連
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

