#include "PSO.h"

PSO::PSO(D3D12_INPUT_LAYOUT_DESC inputLayout, ID3D12RootSignature* pRootSig)
	: pDevice(DX12::GetInstance()->GetDevice())
{
	//PipelineStateの設定
	pipelineDesc.SampleMask					   = D3D12_DEFAULT_SAMPLE_MASK;
	pipelineDesc.RasterizerState			   = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	pipelineDesc.RasterizerState.CullMode	   = D3D12_CULL_MODE_NONE;
	pipelineDesc.IBStripCutValue			   = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
	pipelineDesc.PrimitiveTopologyType		   = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	pipelineDesc.NumRenderTargets			   = 1;
	pipelineDesc.RTVFormats[0]				   = DXGI_FORMAT_R8G8B8A8_UNORM;
	pipelineDesc.DSVFormat					   = DXGI_FORMAT_D32_FLOAT;
	pipelineDesc.SampleDesc.Count			   = 1;
	pipelineDesc.SampleDesc.Quality			   = 0;
	pipelineDesc.BlendState					   = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	//TODO:とりあえず深度情報なし→準備ができたら深度ありにする
	pipelineDesc.DepthStencilState.DepthEnable = false;
	//pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	//pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;	
	pipelineDesc.InputLayout				   = inputLayout;
	pipelineDesc.pRootSignature				   = pRootSig;
}

void PSO::CompileAndSetVS(const LPCWSTR& filePath, LPCSTR entryPoint)
{
	ComPtr<ID3DBlob> errorBlob = nullptr;

	auto result = D3DCompileFromFile(
		/*pFileName		*/ filePath,
		/*pDefines		*/ nullptr,
		/*pInclude		*/ D3D_COMPILE_STANDARD_FILE_INCLUDE,
		/*pEntryPoint	*/ entryPoint,
		/*ShaderVersion	*/ "vs_5_0",
		/*Flag1			*/ D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		/*Flag2			*/ 0,
		/*ppBlob		*/ mVSBlob.GetAddressOf(),
		/*ppErrorBlob	*/ errorBlob.GetAddressOf()
	);

#ifdef _DEBUG
	//エラー処理
	if (FAILED(result))
	{
		if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		{
			::OutputDebugStringA("ファイルが見つかりません");
			return;
		}
		else
		{
			std::string errstr;
			errstr.resize(errorBlob->GetBufferSize());

			std::copy_n((char*)errorBlob->GetBufferPointer(),
				errorBlob->GetBufferSize(),
				errstr.begin()
			);
			errstr += "\n";

			::OutputDebugStringA(errstr.c_str());
		}
	}

#endif
	//解放
	errorBlob.Reset();

	pipelineDesc.VS = CD3DX12_SHADER_BYTECODE(mVSBlob.Get());
}

void PSO::CompileAndSetPS(const LPCWSTR& filePath, LPCSTR entryPoint)
{
	ComPtr<ID3DBlob> errorBlob = nullptr;

	auto result = D3DCompileFromFile(
		/*pFileName		*/ filePath,
		/*pDefines		*/ nullptr,
		/*pInclude		*/ D3D_COMPILE_STANDARD_FILE_INCLUDE,
		/*pEntryPoint	*/ entryPoint,
		/*ShaderVersion	*/ "ps_5_0",
		/*Flag1			*/ D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		/*Flag2			*/ 0,
		/*ppBlob		*/ mPSBlob.GetAddressOf(),
		/*ppErrorBlob	*/ errorBlob.GetAddressOf()
	);

#ifdef _DEBUG
	//エラー処理
	if (FAILED(result))
	{
		if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) 
		{
			::OutputDebugStringA("ファイルが見つかりません");
			return;
		}
		else
		{
			std::string errstr;
			errstr.resize(errorBlob->GetBufferSize());

			std::copy_n((char*)errorBlob->GetBufferPointer(),
				errorBlob->GetBufferSize(),
				errstr.begin()
			);
			errstr += "\n";

			::OutputDebugStringA(errstr.c_str());
		}
	}
#endif

	//解放
	errorBlob.Reset();

	pipelineDesc.PS = CD3DX12_SHADER_BYTECODE(mPSBlob.Get());
}

void PSO::CreatePipeline()
{
	auto result = pDevice->CreateGraphicsPipelineState(
		/*D3D12_GRAPHICS_PIPELINE_STATE_DESC*/ &pipelineDesc,
		/*ppPipelineState					*/ IID_PPV_ARGS(mPipeline.ReleaseAndGetAddressOf())
	);

	if (FAILED(result))
	{
#ifdef _DEBUG
		std::cout << "Pipelineの生成に失敗" << std::endl;
#endif
	}
}

PSO::~PSO()
{
	mPipeline.Reset();
	mVSBlob.Reset();
	mPSBlob.Reset();
}