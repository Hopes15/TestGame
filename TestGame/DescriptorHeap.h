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
	/// DescriptorHeap�N���X��������
	/// </summary>
	DescriptorHeap();

	/// <summary>
	/// DescriptorHeap��CBV, SRV, UAV�̂ǂꂩ�ō쐬
	/// </summary>
	/// <param name="numDescriptors">View(Descriptor)�̐�</param>
	void CreateAsCBV_SRV_UAV(UINT numDescriptors);

	/// <summary>
	/// DescriptorHeap��RTV�ō쐬
	/// </summary>
	/// <param name="numDescriptors">View(Descriptor)�̐�</param>
	void CreateAsRTV(UINT numDescriptors);

	/// <summary>
	/// DescriptorHeap��DSV�ō쐬
	/// </summary>
	/// <param name="numDescriptors">View(Descriptor)�̐�</param>
	void CreateAsDSV(UINT numDescriptors);

	~DescriptorHeap();

	/// <summary>
	/// DescriptorHeap�̃|�C���^�[��Ԃ�
	/// </summary>
	/// <returns>ComPtr.Get()</returns>
	inline ID3D12DescriptorHeap*  GetPointerOfDescriptorHeap() { return mDescHeap.Get(); }

	/// <summary>
	/// DescriptorHeap�̃A�h���X��Ԃ�
	/// </summary>
	/// <returns>ComPtr.GetAddressOf()</returns>
	inline ID3D12DescriptorHeap** GetAddressOfDescriptorHeap() { return mDescHeap.GetAddressOf(); }

private:
	ID3D12Device*				 pDevice   = nullptr;
	ComPtr<ID3D12DescriptorHeap> mDescHeap = nullptr;
};

