#pragma once

#include "DX12.h"

class Component
{
public:
	Component();
	~Component();

protected:
	DX12* mDX12 = nullptr;
};

