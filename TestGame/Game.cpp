#include "Game.h"

void Game::Initialize()
{
	//ウィンドウ作成
	mWindow.SetUpWindow(WIDTH, HEIGHT, L"Pong Game");

	//FPSManager(60FPSに指定)
	//TODO:なぜかフレームレート上限なしになる
	pFPSManager = new FPSManager(60);

	//DX12エンジンを作成
	DX12::Create(WIDTH, HEIGHT, mWindow.GetWindowHandler());
	pDX12 = DX12::GetInstance();
	
	//Inputクラスを作成
	pInput = new Input(mWindow.GetWindowHandler());

	//バックバッファー生成
	pBackBuff = new BackBuffer();

	InitGameSystem();
}

void Game::RunLoop()
{
	bool isActive = true;
	while (isActive)
	{
		isActive = mWindow.GetMSG();

		InputActions();
		Update();
		Output();

		pFPSManager->CalcFPS();
		//pFPSManager->OutputFPS();
	}
}

void Game::Quit()
{
	delete pPlayer2;
	delete pPlayer1;
	delete pWall_B;
	delete pWall_T;
	delete pBall;
	delete pInput;
	delete pBackBuff;
	delete pFPSManager;
	DX12::Destroy();
	mWindow.QuitApp();
}

void Game::InputActions()
{
	//Player1
	if		(pInput->GetKey(DIK_W)) mP1_Dir = -1;
	else if (pInput->GetKey(DIK_S)) mP1_Dir =  1;
	else							mP1_Dir =  0;

	//Player2
	if		(pInput->GetKey(DIK_UP))   mP2_Dir = -1;
	else if (pInput->GetKey(DIK_DOWN)) mP2_Dir =  1;
	else							   mP2_Dir =  0;

	//Spaceを押したらゲームをリスタート
	if (pInput->GetKey(DIK_SPACE) && !mIsPlaying)
	{
		mIsPlaying = true;
		InitGameSystem();
	}
}

void Game::Update()
{
	auto deltaTime = pFPSManager->GetDeltaTime();

	//PLAYER1
	////////////////////////////////////////////////////////////////////
	auto topLimit    = WALL_HEIGHT;
	auto bottomLimit = HEIGHT - (WALL_HEIGHT + PADDLE_HEIGHT);
	pPlayer1->mTransform.position.y += mP1_Dir * SPEED_PLAYER * deltaTime;
	if		(pPlayer1->mTransform.position.y < topLimit)
	{
			 pPlayer1->mTransform.position.y = topLimit;
	}
	else if (pPlayer1->mTransform.position.y > bottomLimit)
	{
			 pPlayer1->mTransform.position.y = bottomLimit;
	}
	////////////////////////////////////////////////////////////////////

	//PLAYER2
	////////////////////////////////////////////////////////////////////
	pPlayer2->mTransform.position.y += mP2_Dir * SPEED_PLAYER * deltaTime;
	if		(pPlayer2->mTransform.position.y < topLimit)
	{
			 pPlayer2->mTransform.position.y = topLimit;
	}
	else if (pPlayer2->mTransform.position.y > bottomLimit)
	{
			 pPlayer2->mTransform.position.y = bottomLimit;
	}
	////////////////////////////////////////////////////////////////////

	//BALL
	//////////////////////////////////////////////////////////////////// 
	pBall->mTransform.position.x += mBall_DirX * SPEED_BALL * deltaTime;
	pBall->mTransform.position.y += mBall_DirY * SPEED_BALL * deltaTime;

	//壁との判定
	topLimit = WALL_HEIGHT;
	bottomLimit = HEIGHT - (WALL_HEIGHT + BALL_HEIGHT);
	if		(pBall->mTransform.position.y <= topLimit && mBall_DirY < 0)
	{
			 mBall_DirY *= -1;
	}
	else if (pBall->mTransform.position.y >= bottomLimit && mBall_DirY > 0)
	{
			 mBall_DirY *= -1;
	}

	//パドルとの判定
	auto diff = (pBall->mTransform.position.y + BALL_HEIGHT / 2.0f) - (pPlayer1->mTransform.position.y + PADDLE_HEIGHT / 2.0f);
	diff = (diff > 0.0f) ? diff : -diff; //絶対値を求める
	if (
		diff <= PADDLE_HEIGHT / 2.0f &&
		(pBall->mTransform.position.x + BALL_WIDTH / 2.0f) <= PADDLE_WIDTH &&
		(pBall->mTransform.position.x + BALL_WIDTH / 2.0f) >= 0			   &&
		mBall_DirX < 0
		)
	{
		mBall_DirX *= -1;
	}

	diff = (pBall->mTransform.position.y + BALL_HEIGHT / 2.0f) - (pPlayer2->mTransform.position.y + PADDLE_HEIGHT / 2.0f);
	diff = (diff > 0.0f) ? diff : -diff; //絶対値を求める
	if (
		diff <= PADDLE_HEIGHT / 2.0f &&
		(pBall->mTransform.position.x + BALL_WIDTH / 2.0f) >= WIDTH - PADDLE_WIDTH &&
		(pBall->mTransform.position.x + BALL_WIDTH / 2.0f) <= WIDTH				   &&
		mBall_DirX > 0
		)
	{
		mBall_DirX *= -1;
	}
	////////////////////////////////////////////////////////////////////

	//勝利判定
	if ((pBall->mTransform.position.x + BALL_WIDTH / 2.0f) < 0)
	{
		mIsPlaying = false;
		mWin = -1;
	}
	else if ((pBall->mTransform.position.x + BALL_WIDTH / 2.0f) > WIDTH)
	{
		mIsPlaying = false;
		mWin =  1;
	}
	else
	{
		mWin = 0;
	}

	SPEED_BALL   += 0.1f;
	SPEED_PLAYER += 0.1f;

	//バッファ更新
	pPlayer1->Update();
	pPlayer2->Update();
	pBall	->Update();
}

void Game::Output()
{
	////////////////////////////////////////////////////////////////////
	//描画準備
	pDX12->EnterDrawing();

	//画面クリア色
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	switch(mWin)
	{
	case  1:
		clearColor[0] = 0.3f;
		break;
	case -1:
		clearColor[2] = 0.3f;
		break;
	}

	//バックバッファーの準備
	pBackBuff->OpenBackBuffer(clearColor);
	////////////////////////////////////////////////////////////////////
	//描画
	pBall	->Draw();
	pWall_T ->Draw();
	pWall_B ->Draw();
	pPlayer1->Draw();
	pPlayer2->Draw();

	////////////////////////////////////////////////////////////////////
	//バックバッファーの描画終了処理
	pBackBuff->CloseBackBuffer();

	//描画終了
	pDX12->ExitDrawing();
	////////////////////////////////////////////////////////////////////
}

void Game::InitGameSystem()
{
	//初期化
	mP1_Dir		 =  0;
	mP2_Dir		 =  0;
	
	//X方向
	if (Random() == 1) mBall_DirX =  1;
	else			   mBall_DirX = -1;
	
	//Y方向
	if (Random() == 1) mBall_DirY =  1;
	else			   mBall_DirY = -1;

	mWin		 =  0;
	SPEED_PLAYER =  300.0f;
	SPEED_BALL   =	150.0f;
	//ゲーム処理
	////////////////////////////////////////////////////////////////////
	//ボール
	Transform trans_Ball = {};
	auto x_Ball = (WIDTH / 2) - (BALL_WIDTH / 2);
	auto y_Ball = (HEIGHT / 2) - (BALL_HEIGHT / 2);
	trans_Ball.SetPosition(x_Ball, y_Ball, 0);

	XMFLOAT4 col_Ball = { 1, 1, 1, 1 };
	pBall = new GameEngine::Rectangle(col_Ball, BALL_WIDTH, BALL_HEIGHT);
	pBall->SetUpTransform(trans_Ball);

	//壁
	Transform trans_Wall[2] = {};
	trans_Wall[0].SetPosition(0, 0, 0);						//上用
	trans_Wall[1].SetPosition(0, HEIGHT - WALL_HEIGHT, 0);	//下用

	//壁上
	XMFLOAT4 col_Wall = { 1, 1, 1, 1 };
	pWall_T = new GameEngine::Rectangle(col_Wall, WALL_WIDTH, WALL_HEIGHT);
	pWall_T->SetUpTransform(trans_Wall[0]);

	//壁下
	pWall_B = new GameEngine::Rectangle(col_Wall, WALL_WIDTH, WALL_HEIGHT);
	pWall_B->SetUpTransform(trans_Wall[1]);

	//パドル(プレイヤー)
	Transform trans_Paddle[2] = {};
	auto x_P1 = 0.0f;
	auto x_P2 = WIDTH - PADDLE_WIDTH;
	auto y_Player = (HEIGHT - PADDLE_HEIGHT) / 2.0f; //パドルを真ん中に配置
	trans_Paddle[0].SetPosition(x_P1, y_Player, 0);
	trans_Paddle[1].SetPosition(x_P2, y_Player, 0);

	XMFLOAT4 col_P1 = { 1, 0, 0, 1 };
	pPlayer1 = new GameEngine::Rectangle(col_P1, PADDLE_WIDTH, PADDLE_HEIGHT);
	pPlayer1->SetUpTransform(trans_Paddle[0]);

	XMFLOAT4 col_P2 = { 0, 0, 1, 1 };
	pPlayer2 = new GameEngine::Rectangle(col_P2, PADDLE_WIDTH, PADDLE_HEIGHT);
	pPlayer2->SetUpTransform(trans_Paddle[1]);

	/////////////////////////////////////////////////////////////////////
}

int Game::Random()
{
	std::random_device rand;
	std::mt19937 mt(rand());
	std::uniform_int_distribution<> rand_Range(0, 1);

	return rand_Range(mt);
}
