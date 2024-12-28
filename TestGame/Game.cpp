#include "Game.h"

void Game::Initialize()
{
	const UINT WIDTH  = 1920;
	const UINT HEIGHT = 1080;

	//ウィンドウ作成
	mWindow.SetUpWindow(WIDTH, HEIGHT, L"TestGame");

	//DX12エンジンを作成
	DX12::Create(WIDTH, HEIGHT, mWindow.GetWindowHandler());
	pDX12 = DX12::GetInstance();

	//バックバッファー生成
	pBackBuff = new BackBuffer();

	//ボール用の初期値設定
	const float BALL_WIDTH  = 10.0f;
	const float BALL_HEIGHT = 10.0f;

	Transform trans_Ball = {};
	auto x  = (WIDTH  / 2) - (BALL_WIDTH  / 2);
	auto y  = (HEIGHT / 2) - (BALL_HEIGHT / 2);
	trans_Ball.SetPosition(0, 0, 0);

	//ボール
	pBall = new GameEngine::Rectangle(BALL_WIDTH, BALL_HEIGHT);
	pBall->SetUpTransform(trans_Ball);

	//壁用の設定
	const float WALL_WIDTH  = WIDTH;
	const float WALL_HEIGHT = 20.0f;

	Transform trans_Wall[2] = {};
	trans_Wall[0].SetPosition(0, 0, 0);						//上用
	trans_Wall[1].SetPosition(0, HEIGHT - WALL_HEIGHT, 0);	//下用

	pWall_T = new GameEngine::Rectangle(WALL_WIDTH, WALL_HEIGHT);
	pWall_T->SetUpTransform(trans_Wall[0]);

	pWall_B = new GameEngine::Rectangle(WALL_WIDTH, WALL_HEIGHT);
	pWall_B->SetUpTransform(trans_Wall[1]);
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
	pBall->Update();
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
	pBall->Draw();
	pWall_T->Draw();
	pWall_B->Draw();

	////////////////////////////////////////////////////////////////////
	//バックバッファーの描画終了処理
	pBackBuff->CloseBackBuffer();

	//描画終了
	pDX12->ExitDrawing();
	////////////////////////////////////////////////////////////////////
}
