#pragma once
#ifdef _DEBUG
#include <iostream>
#endif

//DirectX12
#include <d3d12.h>
#include <d3dx12.h>
#pragma comment (lib, "d3d12.lib")

#include <wrl.h>
using namespace Microsoft::WRL;

#include "DX12.h"

class RootSignature
{
public:
	/// <summary>
	/// RootSignatureクラスを初期化
	/// </summary>
	/// <param name="pRootSigDesc">RootSignatureDescのポインタ</param>
	RootSignature(D3D12_ROOT_SIGNATURE_DESC* pRootSigDesc);
	
	/// <summary>
	/// ID3D12RootSignatureオブジェクトを作成する
	/// </summary>
	void CreateRootSignature();

	/// <summary>
	/// ID3D12RootSignatureのポインターを返す
	/// </summary>
	/// <returns>ComPtr.Get()</returns>
	inline ID3D12RootSignature* GetPointerOfRootSignature() { return mRootSig.Get(); }

	~RootSignature();

private:
	ID3D12Device*				pDevice		= nullptr;
	ComPtr<ID3D12RootSignature> mRootSig	= nullptr;
	ComPtr<ID3DBlob>		    rootSigBlob = nullptr;
};

