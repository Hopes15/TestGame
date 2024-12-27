#pragma once
#include "SharedStructs.h"
#include "DescriptorHeap.h"
#include "ConstantBuffer.h"

struct VP {
	XMMATRIX view;
	XMMATRIX proj;
};

class Camera3D
{
public:
	Camera3D(float WIDTH, float HEIGHT, ID3D12Device* pDevice);
	~Camera3D();

private:
	VP vp = {};

	DescriptorHeap* pDescHeap	  = nullptr;
	ConstantBuffer* pConstantBuff = nullptr;
};

class Camera2D {

};

