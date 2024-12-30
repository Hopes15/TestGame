#pragma once
#include "Window.h"
#include "FPSManager.h"
#include "DX12.h"
#include "BackBuffer.h"
#include "Rectangle.h"
#include "SharedStructs.h"
#include "Input.h"

class Game
{
public:
	void Initialize();

	void RunLoop();

	void Quit();

private:
	void InputActions();

	void Update();

	void Output();

private:
	Window		mWindow;
	FPSManager* pFPSManager = nullptr;
	DX12*		pDX12		= nullptr;
	BackBuffer* pBackBuff	= nullptr;
	Input*		pInput		= nullptr;

	GameEngine::Rectangle* pBall   = nullptr;
	GameEngine::Rectangle* pWall_T = nullptr;
	GameEngine::Rectangle* pWall_B = nullptr;

	bool mKey_W = false;
	bool mKey_S = false;
	bool mKey_A = false;
	bool mKey_D = false;

	const float SPEED = 100.0f;
};

