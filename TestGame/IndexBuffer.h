#pragma once
#ifdef _DEBUG
#include <iostream>
#endif

//DirectX12
#include <d3dx12.h>
#pragma comment (lib, "d3d12.lib")

#include <wrl.h>
using namespace Microsoft::WRL;

#include "DX12.h"

class IndexBuffer
{
public:
	/// <summary>
	/// IndexBuffer�̏�����
	/// </summary>
	/// <param name="bufferSize">IndexBuffer�̃T�C�Y</param>
	IndexBuffer(UINT64 bufferSize);

	/// <summary>
	/// IndexBuffer��VRAM�փR�s�[����
	/// </summary>
	/// <param name="pIndices">�C���f�b�N�X�z��̃A�h���X</param>
	void CopyBufferToVRAM(void* pIndices);

	~IndexBuffer();

	/// <summary>
	/// IndexBufferView�̃A�h���X��Ԃ�
	/// </summary>
	/// <returns>D3D12_INDEX_BUFFER_VIEW mIBV</returns>
	inline D3D12_INDEX_BUFFER_VIEW* GetView() { return &mIBV; }

private:
	D3D12_INDEX_BUFFER_VIEW mIBV = {};

	ID3D12Device* pDevice = nullptr;
	ComPtr<ID3D12Resource> mIndexBuffer = nullptr;
};

