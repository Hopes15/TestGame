#include "BackBuffer.h"

BackBuffer::BackBuffer() : pDX12(DX12::GetInstance())
{
	//DescriptorHeap���쐬
	pRTVDescHeap = new DescriptorHeap();
	pRTVDescHeap->CreateAsRTV(pDX12->BUFFER_COUNT);

	//sRGB�p
	D3D12_RENDER_TARGET_VIEW_DESC RTVdesc = {};
	RTVdesc.Format		  = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	RTVdesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	//RTV�̐���
	//�o�b�N�o�b�t�@�̐������\�[�X��p��
	mBackBuffers.resize(pDX12->BUFFER_COUNT);
	auto handle = pRTVDescHeap->GetPointerOfDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();

	for (UINT i = 0; i < pDX12->BUFFER_COUNT; ++i)
	{
		//�o�b�t�@�[�擾
		auto result = pDX12->GetSwapChain4()->GetBuffer(i, IID_PPV_ARGS(mBackBuffers[i].ReleaseAndGetAddressOf()));

		if (FAILED(result))
		{
#ifdef _DEBUG
			std::cout << "BackBuffer(ID3D12Resource)�̐����Ɏ��s" << std::endl;
#endif
		}
		//RTV����
		pDX12->GetDevice()->CreateRenderTargetView(mBackBuffers[i].Get(), nullptr, handle);
		//�|�C���^�[�����炷
		handle.ptr += pDX12->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	//�r���[�|�[�g�̐ݒ�
	mViewPort.Width    = static_cast<FLOAT>(pDX12->WINDOW_WIDTH);
	mViewPort.Height   = static_cast<FLOAT>(pDX12->WINDOW_HEIGHT);
	mViewPort.TopLeftX = 0;
	mViewPort.TopLeftY = 0;
	mViewPort.MaxDepth = 1.0f;
	mViewPort.MinDepth = 0.0f;

	//�V�U�[��`�̐ݒ�
	mScissorRect.top    = 0;
	mScissorRect.bottom = mScissorRect.top  + pDX12->WINDOW_HEIGHT;
	mScissorRect.left   = 0;
	mScissorRect.right  = mScissorRect.left + pDX12->WINDOW_WIDTH;
}

void BackBuffer::OpenBackBuffer(const float* clearColor)
{
	auto cmdList	 = pDX12->GetCmdList();
	auto backBuffIdx = pDX12->GetSwapChain4()->GetCurrentBackBufferIndex();

	//���\�[�X�o���A
	auto transition = CD3DX12_RESOURCE_BARRIER::Transition(
		/*pResouce*/ mBackBuffers[backBuffIdx].Get(),
		/*Before  */ D3D12_RESOURCE_STATE_PRESENT,
		/*After   */ D3D12_RESOURCE_STATE_RENDER_TARGET
	);
	cmdList->ResourceBarrier(1, &transition);

	//�����_�[�^�[�Q�b�g
	auto RTVHandler = pRTVDescHeap->GetPointerOfDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
	RTVHandler.ptr += backBuffIdx * pDX12->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	//�����_�[�^�[�Q�b�g���Z�b�g
	cmdList->OMSetRenderTargets(1, &RTVHandler, false, nullptr);

	//�����_�[�^�[�Q�b�g���N���A
	cmdList->ClearRenderTargetView(RTVHandler, clearColor, 0, nullptr);

	//�r���[�|�[�g�E�V�U�[��`���Z�b�g
	cmdList->RSSetViewports(1, &mViewPort);
	cmdList->RSSetScissorRects(1, &mScissorRect);
}

void BackBuffer::CloseBackBuffer()
{
	auto cmdList	 = pDX12->GetCmdList();
	auto backBuffIdx = pDX12->GetSwapChain4()->GetCurrentBackBufferIndex();

	//���\�[�X�o���A
	auto transition = CD3DX12_RESOURCE_BARRIER::Transition(
		/*pResouce*/ mBackBuffers[backBuffIdx].Get(),
		/*Before  */ D3D12_RESOURCE_STATE_RENDER_TARGET,
		/*After   */ D3D12_RESOURCE_STATE_PRESENT
	);
	cmdList->ResourceBarrier(1, &transition);
}

BackBuffer::~BackBuffer()
{
	for (auto& backBuff : mBackBuffers) backBuff.Reset();
	delete pRTVDescHeap;
}
