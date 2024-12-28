#pragma once
#include "Window.h"
#include "DX12.h"
#include "BackBuffer.h"
#include "Rectangle.h"
#include "SharedStructs.h"

class Game
{
public:
	void Initialize();

	void RunLoop();

	void Quit();

private:
	void Input();

	void Update();

	void Output();

private:
	Window		mWindow;
	DX12*		pDX12	  = nullptr;
	BackBuffer* pBackBuff = nullptr;

	GameEngine::Rectangle* pBall   = nullptr;
	GameEngine::Rectangle* pWall_T = nullptr;
	GameEngine::Rectangle* pWall_B = nullptr;
};

