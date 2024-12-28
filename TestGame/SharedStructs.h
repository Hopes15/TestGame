#pragma once
#include <DirectXMath.h>

using namespace DirectX;

struct Transform
{
	XMFLOAT3 position = { 0, 0, 0 };
	XMFLOAT3 rotation = { 0, 0, 0 };
	XMFLOAT3 scale	  = { 1, 1, 1 };

	inline void SetPosition(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	};

	inline void SetRotation(float x, float y, float z)
	{
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
	};

	inline void SetScale(float x, float y, float z)
	{
		scale.x = x;
		scale.y = y;
		scale.z = z;
	};
};