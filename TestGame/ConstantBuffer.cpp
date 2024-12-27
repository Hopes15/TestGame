#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(UINT64 bufferSize, D3D12_CPU_DESCRIPTOR_HANDLE handle)
	: pDevice(DX12::GetInstance()->GetDevice())
{
	//���\�[�X����
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
		std::cout << "ConstantBuffer�̐����Ɏ��s" << std::endl;
#endif
	}

	//�R���X�^���g�o�b�t�@�[�r���[�̐ݒ�
	mCBV.BufferLocation = mConstantBuff->GetGPUVirtualAddress();
	mCBV.SizeInBytes	= static_cast<UINT>(bufferSize); //�S�o�C�g

	//�R���X�^���g�o�b�t�@�[�r���[���쐬
	pDevice->CreateConstantBufferView(&mCBV, handle);
}

void ConstantBuffer::CopyBufferToVRAM(void* pSomeThing)
{
	void* pMappedSomeThing = nullptr;
	auto result = mConstantBuff->Map(0, nullptr, (void**)&pMappedSomeThing);

	if (FAILED(result)) {
#ifdef _DEBUG
		std::cout << "ConstantBuffer�̃}�b�s���O�Ɏ��s" << std::endl;
#endif
	}
	memcpy(pMappedSomeThing, pSomeThing, mCBV.SizeInBytes);
	//ConstantBuffer��Unmap���Ȃ��Ă悢�H
	//mConstantBuff->Unmap(0, nullptr);
}

ConstantBuffer::~ConstantBuffer()
{
	mConstantBuff.Reset();
}
