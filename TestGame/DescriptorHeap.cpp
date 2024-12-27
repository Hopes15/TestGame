#include "DescriptorHeap.h"
#include "DX12.h"

DescriptorHeap::DescriptorHeap() : pDevice(DX12::GetInstance()->GetDevice()) {}

void DescriptorHeap::CreateAsCBV_SRV_UAV(UINT numDescriptors)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type			= D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	desc.NodeMask		= 0;
	desc.NumDescriptors = numDescriptors;
	desc.Flags			= D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	//�f�B�X�N���v�^�q�[�v�̐���
	auto result = pDevice->CreateDescriptorHeap(
		/*pDescriptorHeapDesc*/ &desc,
		/*ppDescriptorHeap   */ IID_PPV_ARGS(mDescHeap.ReleaseAndGetAddressOf())
	);

	if (FAILED(result)) 
	{
#ifdef _DEBUG
		std::cout << "�f�B�X�N���v�^�q�[�v�̐����Ɏ��s" << std::endl;
#endif
	}
}

void DescriptorHeap::CreateAsRTV(UINT numDescriptors)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type			= D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	desc.NodeMask		= 0;
	desc.NumDescriptors = numDescriptors;
	desc.Flags			= D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	//�f�B�X�N���v�^�q�[�v�̐���
	auto result = pDevice->CreateDescriptorHeap(
		/*pDescriptorHeapDesc*/ &desc,
		/*ppDescriptorHeap   */ IID_PPV_ARGS(mDescHeap.ReleaseAndGetAddressOf())
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "�f�B�X�N���v�^�q�[�v�̐����Ɏ��s" << std::endl;
#endif
	}
}

void DescriptorHeap::CreateAsDSV(UINT numDescriptors)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type			= D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	desc.NodeMask		= 0;
	desc.NumDescriptors = numDescriptors;
	desc.Flags			= D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	//�f�B�X�N���v�^�q�[�v�̐���
	auto result = pDevice->CreateDescriptorHeap(
		/*pDescriptorHeapDesc*/ &desc,
		/*ppDescriptorHeap   */ IID_PPV_ARGS(mDescHeap.ReleaseAndGetAddressOf())
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "�f�B�X�N���v�^�q�[�v�̐����Ɏ��s" << std::endl;
#endif
	}
}

DescriptorHeap::~DescriptorHeap()
{
	mDescHeap.Reset();
}
