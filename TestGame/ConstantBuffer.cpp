#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(UINT64 bufferSize, D3D12_CPU_DESCRIPTOR_HANDLE handle)
	: pDevice(DX12::GetInstance()->GetDevice())
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
		/*ppResource	 */ IID_PPV_ARGS(mConstantBuff.ReleaseAndGetAddressOf())
	);

	if (FAILED(result)) {
#ifdef _DEBUG
		std::cout << "ConstantBufferの生成に失敗" << std::endl;
#endif
	}

	//コンスタントバッファービューの設定
	mCBV.BufferLocation = mConstantBuff->GetGPUVirtualAddress();
	mCBV.SizeInBytes	= static_cast<UINT>(bufferSize); //全バイト

	//コンスタントバッファービューを作成
	pDevice->CreateConstantBufferView(&mCBV, handle);
}

void ConstantBuffer::CopyBufferToVRAM(void* pSomeThing)
{
	void* pMappedSomeThing = nullptr;
	auto result = mConstantBuff->Map(0, nullptr, (void**)&pMappedSomeThing);

	if (FAILED(result)) {
#ifdef _DEBUG
		std::cout << "ConstantBufferのマッピングに失敗" << std::endl;
#endif
	}
	memcpy(pMappedSomeThing, pSomeThing, mCBV.SizeInBytes);
	//ConstantBufferはUnmapしなくてよい？
	//mConstantBuff->Unmap(0, nullptr);
}

ConstantBuffer::~ConstantBuffer()
{
	mConstantBuff.Reset();
}
