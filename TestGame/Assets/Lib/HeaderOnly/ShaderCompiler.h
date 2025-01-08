#pragma once
#ifdef _DEBUG
#include <iostream>
#endif

//SHaderCompiler
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

/// <summary>
/// �V�F�[�_�[�R���p�C���[
/// </summary>
/// <param name="filePath">�V�F�[�_�[�t�@�C���p�X</param>
/// <param name="version">�V�F�[�_�[�̃o�[�W����</param>
/// <param name="entryPoint">�V�F�[�_�[�̃G���g���[�|�C���g</param>
/// <returns>ID3DBlob*</returns>
inline ID3DBlob* CompileShader(const LPCWSTR& filePath, LPCSTR version, LPCSTR entryPoint)
{
	ID3DBlob* vsBlob  = nullptr;
	ID3DBlob* errBlob = nullptr;

	auto result = D3DCompileFromFile(
		/*pFileName		*/ filePath,
		/*pDefines		*/ nullptr,
		/*pInclude		*/ D3D_COMPILE_STANDARD_FILE_INCLUDE,
		/*pEntryPoint	*/ entryPoint,
		/*ShaderVersion	*/ version,
		/*Flag1			*/ D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		/*Flag2			*/ 0,
		/*ppBlob		*/ &vsBlob,
		/*ppErrorBlob	*/ &errBlob
	);

#ifdef _DEBUG
	//�G���[����
	if (FAILED(result))
	{
		if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		{
			::OutputDebugStringA("�t�@�C����������܂���");
			return nullptr;
		}
		else
		{
			std::string errstr;
			errstr.resize(errBlob->GetBufferSize());

			std::copy_n((char*)errBlob->GetBufferPointer(),
				errBlob->GetBufferSize(),
				errstr.begin()
			);
			errstr += "\n";

			::OutputDebugStringA(errstr.c_str());
		}
	}
#endif

	delete errBlob;

	return vsBlob;
}

