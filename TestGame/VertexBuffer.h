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

class VertexBuffer
{
public:
	/// <summary>
	/// VertexBuffer�̏�����
	/// </summary>
	/// <param name="bufferSize">VertexBuffer�̃T�C�Y</param>
	/// <param name="stride">�P���_�̃T�C�Y</param>
	VertexBuffer(UINT64 bufferSize, UINT stride);

	/// <summary>
	/// VertexBuffer��VRAM�փR�s�[����
	/// </summary>
	/// <param name="pVertices">���_�z��̃A�h���X</param>
	void CopyBufferToVRAM(void* pVertices);

	~VertexBuffer();

	/// <summary>
	/// VertexBufferView�̃A�h���X��Ԃ�
	/// </summary>
	/// <returns>D3D12_VERTEX_BUFFER_VIEW mVBV</returns>
	inline D3D12_VERTEX_BUFFER_VIEW* GetView() { return &mVBV; }

private:
	D3D12_VERTEX_BUFFER_VIEW mVBV = {};

	ID3D12Device*		   pDevice     = nullptr;
	ComPtr<ID3D12Resource> mVertexBuff = nullptr;
};

