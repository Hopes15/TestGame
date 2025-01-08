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

class DescriptorHeap
{
public:
	/// <summary>
	/// DescriptorHeapクラスを初期化
	/// </summary>
	DescriptorHeap();

	/// <summary>
	/// DescriptorHeapをCBV, SRV, UAVのどれかで作成
	/// </summary>
	/// <param name="numDescriptors">View(Descriptor)の数</param>
	void CreateAsCBV_SRV_UAV(UINT numDescriptors);

	/// <summary>
	/// DescriptorHeapをRTVで作成
	/// </summary>
	/// <param name="numDescriptors">View(Descriptor)の数</param>
	void CreateAsRTV(UINT numDescriptors);

	/// <summary>
	/// DescriptorHeapをDSVで作成
	/// </summary>
	/// <param name="numDescriptors">View(Descriptor)の数</param>
	void CreateAsDSV(UINT numDescriptors);

	~DescriptorHeap();

	/// <summary>
	/// DescriptorHeapのポインターを返す
	/// </summary>
	/// <returns>ComPtr.Get()</returns>
	inline ID3D12DescriptorHeap*  GetPointerOfDescriptorHeap() { return mDescHeap.Get(); }

	/// <summary>
	/// DescriptorHeapのアドレスを返す
	/// </summary>
	/// <returns>ComPtr.GetAddressOf()</returns>
	inline ID3D12DescriptorHeap** GetAddressOfDescriptorHeap() { return mDescHeap.GetAddressOf(); }

private:
	ID3D12Device*				 pDevice   = nullptr;
	ComPtr<ID3D12DescriptorHeap> mDescHeap = nullptr;
};

