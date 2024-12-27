#pragma once
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "PSO.h"
#include "RootSignature.h"
#include "SharedStructs.h"
#include "DescriptorHeap.h"

class Triangle
{
public:
	/// <summary>
	/// Triangle�N���X��������
	/// </summary>
	Triangle();

	/// <summary>
	/// ���t���[���X�V�����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�施��
	/// </summary>
	/// <param name="cmdList">ID3D12GraphicsCommandList�̃C���X�^���X</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	~Triangle();

private:
	VertexBuffer*   pVertexBuff   = nullptr;
	ConstantBuffer* pConstantBuff = nullptr;
	DescriptorHeap* pDescHeap	  = nullptr; 
	RootSignature*  pRootSig	  = nullptr;
	PSO*			pPso		  = nullptr;

	XMMATRIX mWorld;

	//TEST
	float x, y, z;
};

