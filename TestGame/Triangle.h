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
	/// Triangleクラスを初期化
	/// </summary>
	Triangle();

	/// <summary>
	/// 毎フレーム更新される
	/// </summary>
	void Update();

	/// <summary>
	/// 描画命令
	/// </summary>
	/// <param name="cmdList">ID3D12GraphicsCommandListのインスタンス</param>
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

