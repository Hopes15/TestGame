#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "PSO.h"
#include "RootSignature.h"
#include "DX12.h"
#include "DescriptorHeap.h"
#include "SharedStructs.h"

namespace GameEngine
{
	class Rectangle
	{
	public:
		/// <summary>
		/// Rectangle�N���X��������
		/// </summary>
		/// <param name="color">�l�p�`�̐F(XMFLOAT4)</param>
		/// <param name="width">��</param>
		/// <param name="height">����</param>
		Rectangle(XMFLOAT4 color = {1, 1, 1, 1}, const float width = 10.0f, const float height = 10.0f);

		/// <summary>
		/// Rectangle��Transform���Z�b�g����
		/// </summary>
		/// <param name="transform"></param>
		void SetUpTransform(Transform& transform);

		/// <summary>
		/// ���t���[���X�V�����
		/// </summary>
		void Update();

		/// <summary>
		/// �`�施��
		/// </summary>
		void Draw();

		~Rectangle();

	public:
		Transform mTransform = {};

	private:
		struct Vertex
		{
			XMFLOAT3 pos;
			XMFLOAT4 color;
		};

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
	};
}


