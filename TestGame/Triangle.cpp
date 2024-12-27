#include "Triangle.h"

Triangle::Triangle() : mWorld(XMMatrixIdentity()), x(0), y(0), z(0)
{
	XMFLOAT3 vertices[] =
	{
		{-0.5f, -0.7f, 0.0f},
		{ 0.0f,  0.7f, 0.0f},
		{ 0.5f, -0.7f, 0.0f}
	};

	UINT64 vertexSize = sizeof(vertices);
	UINT vertexStride = sizeof(XMFLOAT3);

	//頂点用意
	pVertexBuff = new VertexBuffer(vertexSize, vertexStride);
	pVertexBuff->CopyBufferToVRAM(vertices);

	//DescriptorHeap
	pDescHeap = new DescriptorHeap();
	pDescHeap->CreateAsCBV_SRV_UAV(/*numDescriptors = */ 1);

	//World行列(256アライメント)
	UINT64 bufferSize = (sizeof(XMMATRIX) + 0xff) & ~0xff;

	//HeapHandle(Pointer)
	auto handle = pDescHeap->GetPointerOfDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();

	//TODO:View, Projection行列の処理をやる
	//TODO:オブジェクトの動かし方を調べる

	//CBuffを作成
	pConstantBuff = new ConstantBuffer(bufferSize, handle);
	pConstantBuff->CopyBufferToVRAM(&mWorld);

	//RootSignature関連
	{
		//DescriptorRange
		CD3DX12_DESCRIPTOR_RANGE descRanges[1] = {};
		descRanges[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, /*NumDescriptor = */ 1, /*slot = */ 0);

		//RootParameter
		CD3DX12_ROOT_PARAMETER rootParams[1] = {};
		rootParams[0].InitAsDescriptorTable(/*NumDescRanges = */ 1, &descRanges[0]);

		//Sampler
		CD3DX12_STATIC_SAMPLER_DESC samplerDesc[1] = {};
		samplerDesc[0].Init(/*slot = */ 0);

		//RootSignatureDesc
		D3D12_ROOT_SIGNATURE_DESC rootSigDesc = {};
		rootSigDesc.pParameters		  = rootParams;
		rootSigDesc.NumParameters	  = _countof(rootParams);
		rootSigDesc.pStaticSamplers   = samplerDesc;
		rootSigDesc.NumStaticSamplers = _countof(samplerDesc);
		rootSigDesc.Flags			  = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		//ルートシグネチャを作成
		pRootSig = new RootSignature(&rootSigDesc);
		pRootSig->CreateRootSignature();
	}

	//PSO関連
	{
		//インプットレイアウトを作成
		D3D12_INPUT_ELEMENT_DESC elementDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};

		D3D12_INPUT_LAYOUT_DESC inputLayout = {};
		inputLayout.pInputElementDescs = elementDesc;
		inputLayout.NumElements = _countof(elementDesc);

		//PSOを作成
		pPso = new PSO(inputLayout, pRootSig->GetPointerOfRootSignature());
		pPso->CompileAndSetVS(L"Triangle_VS.hlsl");
		pPso->CompileAndSetPS(L"Triangle_PS.hlsl");
		pPso->CreatePipeline();
	}
}

void Triangle::Update()
{
	////表ではUnityみたいに座標変換だけする？
	//x += 0.001f;
	//y += 0.001f;
	//world *= XMMatrixTranslation(x, y, z);

	////裏でこの処理だけをする
	//pConstantBuff->CopyBufferToVRAM(&world);
}

void Triangle::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//Pipeline, RootSignatureをセット
	cmdList->SetPipelineState(pPso->GetPointerOfPipeline());
	cmdList->SetGraphicsRootSignature(pRootSig->GetPointerOfRootSignature());
	
	//PrimitiveTopologyをセット
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//VertexBufferをセット
	cmdList->IASetVertexBuffers(0, 1, pVertexBuff->GetView());

	//World行列をセット
	cmdList->SetDescriptorHeaps(1, pDescHeap->GetAddressOfDescriptorHeap());
	auto heapHandle = pDescHeap->GetPointerOfDescriptorHeap()->GetGPUDescriptorHandleForHeapStart();
	cmdList->SetGraphicsRootDescriptorTable(0, heapHandle);

	//描画
	cmdList->DrawInstanced(3, 1, 0, 0);
}

Triangle::~Triangle()
{
	delete pPso;
	delete pRootSig;
	delete pDescHeap;
	delete pConstantBuff;
	delete pVertexBuff;
}
