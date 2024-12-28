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
		Rectangle(const float width, const float height);

		/// <summary>
		/// RectangleのTransformをセットする
		/// </summary>
		/// <param name="transform"></param>
		void SetUpTransform(Transform& transform);

		/// <summary>
		/// 毎フレーム更新される
		/// </summary>
		void Update();

		/// <summary>
		/// 描画命令
		/// </summary>
		/// <param name="cmdList">ID3D12GraphicsCommandListのインスタンス</param>
		void Draw();

		~Rectangle();

	private:
		void CalcWorldMatrix();

	private:
		VertexBuffer*	pVertexBuff		= nullptr;
		IndexBuffer*	pIndexBuff		= nullptr;
		ConstantBuffer* pCBuff_World	= nullptr;
		ConstantBuffer* pCBuff_ViewProj = nullptr;
		DescriptorHeap* pDescHeap		= nullptr;
		RootSignature*  pRootSig		= nullptr;
		PSO*			pPso			= nullptr;
		DX12*			pDX12			= nullptr;

		XMMATRIX mWorld;
		XMMATRIX mViewProjection;
		Transform mTransform = {};
	};
}


