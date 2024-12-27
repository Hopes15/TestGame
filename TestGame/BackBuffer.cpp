#include "BackBuffer.h"

BackBuffer::BackBuffer() : pDX12(DX12::GetInstance())
{
	//DescriptorHeapを作成
	pRTVDescHeap = new DescriptorHeap();
	pRTVDescHeap->CreateAsRTV(pDX12->BUFFER_COUNT);

	//sRGB用
	D3D12_RENDER_TARGET_VIEW_DESC RTVdesc = {};
	RTVdesc.Format		  = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	RTVdesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	//RTVの生成
	//バックバッファの数分リソースを用意
	mBackBuffers.resize(pDX12->BUFFER_COUNT);
	auto handle = pRTVDescHeap->GetPointerOfDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();

	for (UINT i = 0; i < pDX12->BUFFER_COUNT; ++i)
	{
		//バッファー取得
		auto result = pDX12->GetSwapChain4()->GetBuffer(i, IID_PPV_ARGS(mBackBuffers[i].ReleaseAndGetAddressOf()));

		if (FAILED(result))
		{
#ifdef _DEBUG
			std::cout << "BackBuffer(ID3D12Resource)の生成に失敗" << std::endl;
#endif
		}
		//RTV生成
		pDX12->GetDevice()->CreateRenderTargetView(mBackBuffers[i].Get(), nullptr, handle);
		//ポインターをずらす
		handle.ptr += pDX12->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	//ビューポートの設定
	mViewPort.Width    = static_cast<FLOAT>(pDX12->WINDOW_WIDTH);
	mViewPort.Height   = static_cast<FLOAT>(pDX12->WINDOW_HEIGHT);
	mViewPort.TopLeftX = 0;
	mViewPort.TopLeftY = 0;
	mViewPort.MaxDepth = 1.0f;
	mViewPort.MinDepth = 0.0f;

	//シザー矩形の設定
	mScissorRect.top    = 0;
	mScissorRect.bottom = mScissorRect.top  + pDX12->WINDOW_HEIGHT;
	mScissorRect.left   = 0;
	mScissorRect.right  = mScissorRect.left + pDX12->WINDOW_WIDTH;
}

void BackBuffer::OpenBackBuffer(const float* clearColor)
{
	auto cmdList	 = pDX12->GetCmdList();
	auto backBuffIdx = pDX12->GetSwapChain4()->GetCurrentBackBufferIndex();

	//リソースバリア
	auto transition = CD3DX12_RESOURCE_BARRIER::Transition(
		/*pResouce*/ mBackBuffers[backBuffIdx].Get(),
		/*Before  */ D3D12_RESOURCE_STATE_PRESENT,
		/*After   */ D3D12_RESOURCE_STATE_RENDER_TARGET
	);
	cmdList->ResourceBarrier(1, &transition);

	//レンダーターゲット
	auto RTVHandler = pRTVDescHeap->GetPointerOfDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
	RTVHandler.ptr += backBuffIdx * pDX12->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	//レンダーターゲットをセット
	cmdList->OMSetRenderTargets(1, &RTVHandler, false, nullptr);

	//レンダーターゲットをクリア
	cmdList->ClearRenderTargetView(RTVHandler, clearColor, 0, nullptr);

	//ビューポート・シザー矩形をセット
	cmdList->RSSetViewports(1, &mViewPort);
	cmdList->RSSetScissorRects(1, &mScissorRect);
}

void BackBuffer::CloseBackBuffer()
{
	auto cmdList	 = pDX12->GetCmdList();
	auto backBuffIdx = pDX12->GetSwapChain4()->GetCurrentBackBufferIndex();

	//リソースバリア
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
