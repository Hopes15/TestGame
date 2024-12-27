#include "RootSignature.h"

RootSignature::RootSignature(D3D12_ROOT_SIGNATURE_DESC* pRootSigDesc) : pDevice(DX12::GetInstance()->GetDevice())
{
	//TODO:rootParameter, descTBL, Sampler���O������Z�b�g�ł���悤�ɂ���
	//���[�g�V�O�l�`���f�B�X�N���v�^(��)
	
	ComPtr<ID3DBlob> errBlob = nullptr;

	auto result = D3D12SerializeRootSignature(
		/*D3D12_ROOT_SIGNATURE_DESC	*/ pRootSigDesc,
		/*D3D_ROOT_SIGNATURE_VERSION*/ D3D_ROOT_SIGNATURE_VERSION_1_0,
		/*ppBlob					*/ rootSigBlob.ReleaseAndGetAddressOf(),
		/*ppErrorBlob				*/ errBlob.ReleaseAndGetAddressOf()
	);

	//���[�g�V�O�l�`���̃V���A���C�Y
	if (FAILED(result)) 
	{
#ifdef _DEBUG
		std::cout << "RootSignature�̃V���A���C�Y�Ɏ��s" << std::endl;
#endif
	}

	//���
	errBlob.Reset();
}

void RootSignature::CreateRootSignature()
{
	//���[�g�V�O�l�`���𐶐�
	auto result = pDevice->CreateRootSignature(
		/*nodeMask				*/ 0,
		/*pBlobWithRootSignature*/ rootSigBlob->GetBufferPointer(),
		/*blobLengthInBytes     */ rootSigBlob->GetBufferSize(),
		/*ppRootSignature		*/ IID_PPV_ARGS(mRootSig.ReleaseAndGetAddressOf())
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "RootSignature�̐����Ɏ��s" << std::endl;
#endif
	}

	//���
	rootSigBlob.Reset();
}

RootSignature::~RootSignature()
{
	mRootSig.Reset();
}