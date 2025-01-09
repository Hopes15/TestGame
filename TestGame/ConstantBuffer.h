#pragma once
#ifdef _DEBUG
#include <iostream>
#endif

//DirectX12
#include <d3d12.h>
#include "Assets/Lib/HeaderOnly/d3dx12.h"
#pragma comment (lib, "d3d12.lib")

#include <wrl.h>
using namespace Microsoft::WRL;

#include "DX12.h"

class ConstantBuffer
{
public:
	/// <summary>
	/// ConstantBufferクラスを初期化
	/// </summary>
	/// <param name="bufferSize">ConstantBufferのサイズ</param>
	/// <param name="handle">DescriptorHeapのハンドル（ポインタ）</param>
	ConstantBuffer(UINT64 bufferSize, D3D12_CPU_DESCRIPTOR_HANDLE handle);

	/// <summary>
	/// ConstantBufferをVRAMへコピーする
	/// </summary>
	/// <param name="pSomeThing">コンスタントバッファーに確保する何か</param>
	void CopyBufferToVRAM(void* pSomeThing);

	/// <summary>
	/// ConstantBufferの内容を更新する
	/// </summary>
	/// <param name="pSomeThing">コンスタントバッファーに確保する何か</param>
	void UpdateCBuffer(void* pSomeThing);

	~ConstantBuffer();

private:
	D3D12_CONSTANT_BUFFER_VIEW_DESC mCBV = {};

	void*				   pMappedSomeThing = nullptr;
	ID3D12Device*		   pDevice		    = nullptr;
	ComPtr<ID3D12Resource> mConstantBuff	= nullptr;
};

