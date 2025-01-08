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

#include "DescriptorHeap.h"
#include "DX12.h"

class BackBuffer
{
public:
	BackBuffer();

	/// <summary>
	/// �o�b�N�o�b�t�@�[�ւ̕`�揀������
	/// </summary>
	/// <param name="clearColor">��ʃN���A������F float[] = (R, G, B, A)</param>
	void OpenBackBuffer(const float* clearColor);

	/// <summary>
	/// �o�b�N�o�b�t�@�[�ւ̕`��I������
	/// </summary>
	void CloseBackBuffer();

	~BackBuffer();

private:
	D3D12_VIEWPORT mViewPort	= {};
	D3D12_RECT     mScissorRect = {};

	DescriptorHeap* pRTVDescHeap = nullptr;
	DX12*			pDX12		 = nullptr;
	std::vector<ComPtr<ID3D12Resource>> mBackBuffers;
};

