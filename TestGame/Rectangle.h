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
		/// Rectangle�N���X��������
		/// </summary>
		Rectangle();

		/// <summary>
		/// ���t���[���X�V�����
		/// </summary>
		void Update();

		/// <summary>
		/// �`�施��
		/// </summary>
		/// <param name="cmdList">ID3D12GraphicsCommandList�̃C���X�^���X</param>
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


