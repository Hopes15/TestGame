#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "PSO.h"
#include "RootSignature.h"
#include "DX12.h"
#include "SharedStructs.h"
#include "DescriptorHeap.h"

namespace GameEngine
{
	class Rectangle
	{
	public:
		/// <summary>
		/// Rectangleクラスを初期化
		/// </summary>
		Rectangle();

		/// <summary>
		/// 毎フレーム更新される
		/// </summary>
		void Update();

		/// <summary>
		/// 描画命令
		/// </summary>
		/// <param name="cmdList">ID3D12GraphicsCommandListのインスタンス</param>
		void Draw(ID3D12GraphicsCommandList* cmdList);

		~Rectangle();

	private:
		VertexBuffer* pVertexBuff = nullptr;
		IndexBuffer* pIndexBuff = nullptr;
		ConstantBuffer* pConstantBuff = nullptr;
		DescriptorHeap* pDescHeap = nullptr;
		RootSignature* pRootSig = nullptr;
		PSO* pPso = nullptr;

		XMMATRIX world;

		//TEST
		float x, y, z;
	};
}


