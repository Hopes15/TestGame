#include "Camera.h"

Camera3D::Camera3D(float WIDTH, float HEIGHT, ID3D12Device* device)
{
	//カメラの設定 (x, y, z)
	XMFLOAT3 cam   (0, 20, -15);
	XMFLOAT3 target(0, 12, 0);
	XMFLOAT3 up    (0, 1, 0);

	vp.view	= XMMatrixLookAtLH(XMLoadFloat3(&cam), XMLoadFloat3(&target), XMLoadFloat3(&up));
	vp.proj = XMMatrixPerspectiveFovLH(
		/*画角		 */ XM_PIDIV2,
		/*AspectRatio*/ WIDTH / HEIGHT,
		/*Near面	 */ 0.5f,  
		/*Far面		 */ 1000.0f
	);

	//View, Projection構造体のサイズ(256アライメント)
	UINT64 bufferSize = (sizeof(VP) + 0xff) & ~0xff;

	//DescriptorHeap
	pDescHeap = new DescriptorHeap(device);
	pDescHeap->CreateAsCBV_SRV_UAV(/*numDescriptors = */ 1);

	//HeapHandle(Pointer)
	auto handle = pDescHeap->GetPointerOfDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();

	//CBuffを作成
	pConstantBuff = new ConstantBuffer(bufferSize, handle, device);
	pConstantBuff->CopyBufferToVRAM(&vp);
}

Camera3D::~Camera3D()
{
	delete pConstantBuff;
	delete pDescHeap;
}

/*  XMFLOAT3 cam(0, 20, -15);
	XMFLOAT3 target(0, 12, 0);
	XMFLOAT3 up(0, 1, 0);

	//座標系の初期化
	mView = XMMatrixLookAtLH(XMLoadFloat3(&cam), XMLoadFloat3(&target), XMLoadFloat3(&up));
	mProj = XMMatrixPerspectiveFovLH(
		XM_PIDIV2,
		static_cast<float>(m_pApp->WINDOW_WIDTH) / static_cast<float>(m_pApp->WINDOW_HEIGHT),
		0.5f,   //near
		1000.0f //far
	);
	mCam = cam;

	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	desc.NodeMask = 0;
	desc.NumDescriptors = 1;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	//ディスクリプタヒープの生成
	auto result = mDev->CreateDescriptorHeap(&desc, IID_PPV_ARGS(mVPDescHeap.ReleaseAndGetAddressOf()));

	if (FAILED(result)) {
#ifdef _DEBUG
		std::cout << "ディスクリプタヒープの生成に失敗" << std::endl;
#endif
		return false;
	}

	//定数バッファーの作成
	auto heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto resDesc = CD3DX12_RESOURCE_DESC::Buffer((sizeof(Matrix) + 0xff) & ~0xff);
	result = mDev->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(mResource[1].ReleaseAndGetAddressOf())
	);

	if (FAILED(result)) {
#ifdef _DEBUG
		std::cout << "リソースの生成に失敗" << std::endl;
#endif
		return false;
	}

	//マッピング
	result = mResource[1]->Map(0, nullptr, (void**)&mMatrix);
	mMatrix->view = mView;
	mMatrix->proj = mProj;
	mMatrix->cam = mCam;

	if (FAILED(result)) {
#ifdef _DEBUG
		std::cout << "マッピングに失敗" << std::endl;
#endif
		return false;
	}

	mResource[1]->Unmap(0, nullptr);

	//コンスタントバッファービュー
	mMatrixCBVDesc.BufferLocation = mResource[1]->GetGPUVirtualAddress();
	mMatrixCBVDesc.SizeInBytes = static_cast<UINT>(mResource[1]->GetDesc().Width);

	auto handle = mVPDescHeap->GetCPUDescriptorHandleForHeapStart();
	mDev->CreateConstantBufferView(&mMatrixCBVDesc, handle);
	*/
