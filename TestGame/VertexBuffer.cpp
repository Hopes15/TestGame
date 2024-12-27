#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(UINT64 bufferSize, UINT stride) :
	pDevice(DX12::GetInstance()->GetDevice())
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
		/*ppResource	 */ IID_PPV_ARGS(mVertexBuff.ReleaseAndGetAddressOf())
	);

	if (FAILED(result)) 
	{
#ifdef _DEBUG
		std::cout << "VertexBuffer�̐����Ɏ��s" << std::endl;
#endif
	}

	//�o�[�e�b�N�X�o�b�t�@�r���[�̐ݒ�
	mVBV.BufferLocation = mVertexBuff->GetGPUVirtualAddress();
	mVBV.SizeInBytes	= static_cast<UINT>(bufferSize);   //�S�o�C�g
	mVBV.StrideInBytes	= static_cast<UINT>(stride);	   //���_�������̃T�C�Y
}

void VertexBuffer::CopyBufferToVRAM(void* pVertices)
{
	void* mappedVertices = nullptr;
	auto result = mVertexBuff->Map(0, nullptr, (void**)&mappedVertices);

	if (FAILED(result)) 
	{
#ifdef _DEBUG
		std::cout << "VertexBuffer�̃}�b�s���O�Ɏ��s" << std::endl;
#endif
	}
	memcpy(mappedVertices, pVertices, mVBV.SizeInBytes);
	mVertexBuff->Unmap(0, nullptr);
}

VertexBuffer::~VertexBuffer()
{
	mVertexBuff.Reset();
}
