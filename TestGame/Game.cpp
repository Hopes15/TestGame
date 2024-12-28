#include "Game.h"

void Game::Initialize()
{
	const UINT WIDTH  = 640;
	const UINT HEIGHT = 480;

	const float BALL_WIDTH  = 5.0f;
	const float BALL_HEIGHT = 5.0f;

	//ウィンドウ作成
	mWindow.SetUpWindow(WIDTH, HEIGHT, L"TestGame");

	//DX12エンジンを作成
	DX12::Create(WIDTH, HEIGHT, mWindow.GetWindowHandler());
	pDX12 = DX12::GetInstance();

	//バックバッファー生成
	pBackBuff = new BackBuffer();

	//ボール用の初期値設定
	Transform transform = {};
	auto width  = (WIDTH  / 2) - (BALL_WIDTH  / 2);
	auto height = (HEIGHT / 2) - (BALL_HEIGHT / 2);
	transform.SetPosition(width, height, 0);
	transform.SetScale(10, 20, 0);

	//ボール
	pRectangle = new GameEngine::Rectangle(BALL_WIDTH, BALL_HEIGHT);
	pRectangle->SetUpTransform(transform);
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

}

void Game::Update()
{
	//pRectangle->Update();
}

void Game::Output()
{
	////////////////////////////////////////////////////////////////////
	//描画準備
	pDX12->EnterDrawing();

	//画面クリア色
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	//バックバッファーの準備
	pBackBuff->OpenBackBuffer(clearColor);
	////////////////////////////////////////////////////////////////////

	//描画
	pRectangle->Draw();

	////////////////////////////////////////////////////////////////////
	//バックバッファーの描画終了処理
	pBackBuff->CloseBackBuffer();

	//描画終了
	pDX12->ExitDrawing();
	////////////////////////////////////////////////////////////////////
}
