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
	/// PSO�I�u�W�F�N�g��������, �p�C�v���C���X�e�[�g�ɕK�v�ȗv�f�������ɂƂ�
	/// </summary>
	/// <param name="inputLayout">�Z�b�g����C���v�b�g���C�A�E�g</param>
	/// <param name="pRootSig">�Z�b�g����RootSignature�̃|�C���^</param>
	PSO(D3D12_INPUT_LAYOUT_DESC inputLayout, ID3D12RootSignature *pRootSig);

	/// <summary>
	/// VertexShader���R���p�C�����APipelineStateDesc�ɃZ�b�g����
	/// </summary>
	/// <param name="filePath">VertexShader�̃t�@�C���p�X</param>
	/// <param name="entryPoint">Shader�̃G���g���[�|�C���g�@Default��main</param>
	void CompileAndSetVS(const LPCWSTR& filePath, LPCSTR entryPoint = "main");

	/// <summary>
	/// PixelShader���R���p�C�����APipelineStateDesc�ɃZ�b�g����
	/// </summary>
	/// <param name="filePath">PixelShader�̃t�@�C���p�X</param>
	/// <param name="entryPoint">Shader�̃G���g���[�|�C���g�@Default��main</param>
	void CompileAndSetPS(const LPCWSTR& filePath, LPCSTR entryPoint = "main");

	/// <summary>
	/// ID3D12PipelineState�I�u�W�F�N�g���쐬����
	/// </summary>
	void CreatePipeline();

	/// <summary>
	/// ID3D12PipelineState�̃|�C���^��Ԃ�
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

