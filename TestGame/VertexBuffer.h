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
	/// VertexBufferの初期化
	/// </summary>
	/// <param name="bufferSize">VertexBufferのサイズ</param>
	/// <param name="stride">１頂点のサイズ</param>
	VertexBuffer(UINT64 bufferSize, UINT stride);

	/// <summary>
	/// VertexBufferをVRAMへコピーする
	/// </summary>
	/// <param name="pVertices">頂点配列のアドレス</param>
	void CopyBufferToVRAM(void* pVertices);

	~VertexBuffer();

	/// <summary>
	/// VertexBufferViewのアドレスを返す
	/// </summary>
	/// <returns>D3D12_VERTEX_BUFFER_VIEW mVBV</returns>
	inline D3D12_VERTEX_BUFFER_VIEW* GetView() { return &mVBV; }

private:
	D3D12_VERTEX_BUFFER_VIEW mVBV = {};

	ID3D12Device*		   pDevice     = nullptr;
	ComPtr<ID3D12Resource> mVertexBuff = nullptr;
};

