#include "Game.h"

void Game::Initialize()
{
	const UINT WIDTH  = 640;
	const UINT HEIGHT = 480;

	//ウィンドウ作成
	mWindow.SetUpWindow(WIDTH, HEIGHT, L"TestGame");

	//DX12エンジンを作成
	DX12::Create(WIDTH, HEIGHT, mWindow.GetWindowHandler());
	pDX12 = DX12::GetInstance();

	//バックバッファー生成
	pBackBuff = new BackBuffer();
}

void Game::RunLoop()
{
	bool isActive = true;
	while (isActive)
	{
		isActive = mWindow.GameLoop();

		Input();
		Update();
		Output();
	}
}

void Game::Quit()
{
	delete pBackBuff;
	DX12::Destroy();
	mWindow.QuitApp();
}

void Game::Input()
{
	//描画準備
	pDX12->EnterDrawing();

	//画面クリア色
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	//バックバッファーの準備
	pBackBuff->OpenBackBuffer(clearColor);
}

void Game::Update()
{
}

void Game::Output()
{
	//バックバッファーの描画終了処理
	pBackBuff->CloseBackBuffer();

	//描画終了
	pDX12->ExitDrawing();
}
