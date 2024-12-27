#pragma once
#include <DirectXMath.h>

using namespace DirectX;

struct Transform
{
	XMMATRIX world;

	inline void* operator new(size_t size)
	{
		return _aligned_malloc(size, 16);
	}
};

