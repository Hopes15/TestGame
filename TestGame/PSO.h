#pragma once
#ifdef _DEBUG
#include <iostream>
#endif

//DirectX12
#include <d3d12.h>
#include <d3dx12.h>
#pragma comment (lib, "d3d12.lib")

//SHaderCompiler
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

//ComPtr
#include <wrl.h>
using namespace Microsoft::WRL;

#include "DX12.h"

class PSO
{
public:
	/// <summary>
	/// PSOオブジェクトを初期化, パイプラインステートに必要な要素を引数にとる
	/// </summary>
	/// <param name="inputLayout">セットするインプットレイアウト</param>
	/// <param name="pRootSig">セットするRootSignatureのポインタ</param>
	PSO(D3D12_INPUT_LAYOUT_DESC inputLayout, ID3D12RootSignature *pRootSig);

	/// <summary>
	/// VertexShaderをコンパイルし、PipelineStateDescにセットする
	/// </summary>
	/// <param name="filePath">VertexShaderのファイルパス</param>
	/// <param name="entryPoint">Shaderのエントリーポイント　Defaultはmain</param>
	void CompileAndSetVS(const LPCWSTR& filePath, LPCSTR entryPoint = "main");

	/// <summary>
	/// PixelShaderをコンパイルし、PipelineStateDescにセットする
	/// </summary>
	/// <param name="filePath">PixelShaderのファイルパス</param>
	/// <param name="entryPoint">Shaderのエントリーポイント　Defaultはmain</param>
	void CompileAndSetPS(const LPCWSTR& filePath, LPCSTR entryPoint = "main");

	/// <summary>
	/// ID3D12PipelineStateオブジェクトを作成する
	/// </summary>
	void CreatePipeline();

	/// <summary>
	/// ID3D12PipelineStateのポインタを返す
	/// </summary>
	/// <returns>ComPtr.Get()</returns>
	inline ID3D12PipelineState* GetPointerOfPipeline() { return mPipeline.Get(); }

	~PSO();
private:
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc = {};

	ComPtr<ID3DBlob>			mVSBlob	  = nullptr;
	ComPtr<ID3DBlob>			mPSBlob   = nullptr;
	ComPtr<ID3D12PipelineState> mPipeline = nullptr;
	ID3D12Device*				pDevice   = nullptr;
};

