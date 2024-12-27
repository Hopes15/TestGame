#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(UINT64 bufferSize) : pDevice(DX12::GetInstance()->GetDevice())
{
	//リソース生成
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto resDesc  = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);
	auto result   = pDevice->CreateCommittedResource(
		/*HEAP_PROPERTIES*/ &heapProp,
		/*HEAP_FLAG		 */ D3D12_HEAP_FLAG_NONE,
		/*RESOURCE_DESC  */ &resDesc,
		/*RESOURCE_STATE */ D3D12_RESOURCE_STATE_GENERIC_READ,
		/*CLEAR_VALUE	 */ nullptr,
		/*ppResource	 */ IID_PPV_ARGS(mIndexBuffer.ReleaseAndGetAddressOf())
	);

	if (FAILED(result)) 
	{
#ifdef _DEBUG
		std::cout << "IndexBufferの生成に失敗" << std::endl;
#endif
	}

	//インデックスバッファービューの設定
	mIBV.BufferLocation = mIndexBuffer->GetGPUVirtualAddress();
	mIBV.Format			= DXGI_FORMAT_R16_UINT;
	mIBV.SizeInBytes	= static_cast<UINT>(bufferSize);
}

void IndexBuffer::CopyBufferToVRAM(void* pIndices)
{
	void* mappedIndices = nullptr;
	auto result = mIndexBuffer->Map(0, nullptr, (void**)&mappedIndices);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "IndexBufferのマッピングに失敗" << std::endl;
#endif
	}
	memcpy(mappedIndices, pIndices, mIBV.SizeInBytes);
	mIndexBuffer->Unmap(0, nullptr);
}

IndexBuffer::~IndexBuffer()
{
	mIndexBuffer.Reset();
}
