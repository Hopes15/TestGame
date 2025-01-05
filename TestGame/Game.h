#pragma once
#include "Window.h"
#include "FPSManager.h"
#include "DX12.h"
#include "BackBuffer.h"
#include "Rectangle.h"
#include "SharedStructs.h"
#include "Input.h"
#include <random>

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

	void InitGameSystem();

	int Random();

private:
	Window		mWindow;
	FPSManager* pFPSManager = nullptr;
	DX12*		pDX12		= nullptr;
	BackBuffer* pBackBuff	= nullptr;
	Input*		pInput		= nullptr;

	GameEngine::Rectangle* pBall    = nullptr;
	GameEngine::Rectangle* pWall_T  = nullptr;
	GameEngine::Rectangle* pWall_B  = nullptr;
	GameEngine::Rectangle* pPlayer1 = nullptr;
	GameEngine::Rectangle* pPlayer2 = nullptr;

	int mP1_Dir	   =  0;
	int mP2_Dir	   =  0;
	int mBall_DirX =  0;
	int mBall_DirY =  0;
	int mWin	   =  0; //-1 : Left, 1 : Right

	bool mIsPlaying = true;

	float SPEED_PLAYER  = 0;
	float SPEED_BALL    = 0;

	const UINT  WIDTH		  = 640;
	const UINT  HEIGHT		  = 480;
	const float WALL_WIDTH	  = static_cast<float>(WIDTH);
	const float WALL_HEIGHT   = 10.0f;
	const float PADDLE_WIDTH  = 8.0f;
	const float PADDLE_HEIGHT = 60.0f;
	const float BALL_WIDTH	  = 5.0f;
	const float BALL_HEIGHT   = 5.0f;
};

