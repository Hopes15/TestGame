#include "Rectangle.h"

GameEngine::Rectangle::Rectangle(const float width, const float height) :
	pDX12		   (DX12::GetInstance()),
	mWorld		   (XMMatrixIdentity()),
	mViewProjection(XMMatrixIdentity())
{
	//���_
	XMFLOAT3 vertices[] =
	{
		{  0.0f, height, 0.0f}, //����
		{  0.0f,   0.0f, 0.0f}, //����
		{ width, height, 0.0f}, //�E��
		{ width,   0.0f, 0.0f}  //�E��
	};	

	UINT64 vertexSize = sizeof(vertices);
	UINT vertexStride = sizeof(XMFLOAT3);

	pVertexBuff = new VertexBuffer(vertexSize, vertexStride);
	pVertexBuff->CopyBufferToVRAM(vertices);

	//�C���f�b�N�X
	uint16_t indices[] =
	{
		0, 1, 2,
		2, 1, 3
	};

	UINT64 indexSize = sizeof(indices);
	pIndexBuff = new IndexBuffer(indexSize);
	pIndexBuff->CopyBufferToVRAM(indices);

	//ViewProjection�s��(2D)
	mViewProjection.r[0].m128_f32[0] =  2.0f / pDX12->WINDOW_WIDTH;
	mViewProjection.r[1].m128_f32[1] = -2.0f / pDX12->WINDOW_HEIGHT;
	mViewProjection.r[3].m128_f32[0] = -1.0;
	mViewProjection.r[3].m128_f32[1] =  1.0;

	//DescriptorHeap
	pDescHeap = new DescriptorHeap();
	pDescHeap->CreateAsCBV_SRV_UAV(/*numDescriptors = */ 2);

	//HeapHandle(Pointer)
	auto handle = pDescHeap->GetPointerOfDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();

	//CBuff���쐬(World�s��p)
	UINT64 bufferSize = (sizeof(XMMATRIX) + 0xff) & ~0xff;
	pCBuff_World = new ConstantBuffer(bufferSize, handle);
	pCBuff_World->CopyBufferToVRAM(&mWorld);

	handle.ptr += pDX12->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//CBuff���쐬(ViewProjection�s��p)
	pCBuff_ViewProj = new ConstantBuffer(bufferSize, handle);
	pCBuff_ViewProj->CopyBufferToVRAM(&mViewProjection);

	//RootSignature�֘A
	{
		//DescriptorRange
		CD3DX12_DESCRIPTOR_RANGE descRanges[2] = {};
		//WorldMatrix
		descRanges[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, /*NumDescriptor = */ 1, /*slot = */ 0);
		//ViewProjectionMatrix
		descRanges[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, /*NumDescriptor = */ 1, /*slot = */ 1);

		//RootParameter
		CD3DX12_ROOT_PARAMETER rootParams[1] = {};
		rootParams[0].InitAsDescriptorTable(/*NumDescRanges = */ 2, &descRanges[0]);

		//Sampler
		CD3DX12_STATIC_SAMPLER_DESC samplerDesc[1] = {};
		samplerDesc[0].Init(/*slot = */ 0);

		//RootSignatureDesc
		D3D12_ROOT_SIGNATURE_DESC rootSigDesc = {};
		rootSigDesc.pParameters = rootParams;
		rootSigDesc.NumParameters = _countof(rootParams);
		rootSigDesc.pStaticSamplers = samplerDesc;
		rootSigDesc.NumStaticSamplers = _countof(samplerDesc);
		rootSigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		//���[�g�V�O�l�`�����쐬
		pRootSig = new RootSignature(&rootSigDesc);
		pRootSig->CreateRootSignature();
	}

	//PSO�֘A
	{
		//�C���v�b�g���C�A�E�g���쐬
		D3D12_INPUT_ELEMENT_DESC elementDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};

		D3D12_INPUT_LAYOUT_DESC inputLayout = {};
		inputLayout.pInputElementDescs = elementDesc;
		inputLayout.NumElements = _countof(elementDesc);

		//PSO���쐬
		pPso = new PSO(inputLayout, pRootSig->GetPointerOfRootSignature());
		pPso->CompileAndSetVS(L"Rectangle_VS.hlsl");
		pPso->CompileAndSetPS(L"Rectangle_PS.hlsl");
		pPso->CreatePipeline();
	}
}

void GameEngine::Rectangle::SetUpTransform(Transform& transform)
{
	mTransform = transform;

	mWorld *= XMMatrixScaling(mTransform.scale.x, mTransform.scale.y, mTransform.scale.z);
	mWorld *= XMMatrixRotationZ(mTransform.rotation.z);
	mWorld *= XMMatrixTranslation(mTransform.position.x, mTransform.position.y, mTransform.position.z);
	pCBuff_World->UpdateCBuffer(&mWorld);
}

void GameEngine::Rectangle::Update()
{
	auto translation = XMMatrixTranslation(mTransform.position.x, mTransform.position.y, mTransform.position.z);
	mWorld = translation;
	pCBuff_World->UpdateCBuffer(&mWorld);

	//std::cout << "x : " << mTransform.position.x << " y : " << mTransform.position.y << " z : " << mTransform.position.z << std::endl;
}

void GameEngine::Rectangle::Draw()
{
	auto cmdList = DX12::GetInstance()->GetCmdList();

	//Pipeline, RootSignature���Z�b�g
	cmdList->SetPipelineState(pPso->GetPointerOfPipeline());
	cmdList->SetGraphicsRootSignature(pRootSig->GetPointerOfRootSignature());

	//PrimitiveTopology���Z�b�g
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//VertexBuffer���Z�b�g
	cmdList->IASetVertexBuffers(0, 1, pVertexBuff->GetView());

	//IndexBuffer���Z�b�g
	cmdList->IASetIndexBuffer(pIndexBuff->GetView());

	//CBuffer���Z�b�g
	cmdList->SetDescriptorHeaps(1, pDescHeap->GetAddressOfDescriptorHeap());
	auto heapHandle = pDescHeap->GetPointerOfDescriptorHeap()->GetGPUDescriptorHandleForHeapStart();
	cmdList->SetGraphicsRootDescriptorTable(0, heapHandle);

	//�`��
	cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

GameEngine::Rectangle::~Rectangle()
{
	delete pPso;
	delete pRootSig;
	delete pDescHeap;
	delete pCBuff_ViewProj;
	delete pCBuff_World;
	delete pIndexBuff;
	delete pVertexBuff;
}
