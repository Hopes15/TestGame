#include "Game.h"

void Game::Initialize()
{
	const UINT WIDTH  = 640;
	const UINT HEIGHT = 480;

	//�E�B���h�E�쐬
	mWindow.SetUpWindow(WIDTH, HEIGHT, L"TestGame");

	//FPSCounter(Window�N���X�ɑg�ݍ���ł����������H)
	pFPSManager = new FPSManager(60);

	//DX12�G���W�����쐬
	DX12::Create(WIDTH, HEIGHT, mWindow.GetWindowHandler());
	pDX12 = DX12::GetInstance();
	
	//Input�N���X���쐬
	pInput = new Input(mWindow.GetWindowHandler());

	//�o�b�N�o�b�t�@�[����
	pBackBuff = new BackBuffer();

	//�Q�[������
	////////////////////////////////////////////////////////////////////
	//�{�[���p�̏����l�ݒ�
	const float BALL_WIDTH  = 5.0f;
	const float BALL_HEIGHT = 5.0f;

	Transform trans_Ball = {};
	auto x  = (WIDTH  / 2) - (BALL_WIDTH  / 2);
	auto y  = (HEIGHT / 2) - (BALL_HEIGHT / 2);
	trans_Ball.SetPosition(x, y, 0);

	//�{�[��
	pBall = new GameEngine::Rectangle(BALL_WIDTH, BALL_HEIGHT);
	pBall->SetUpTransform(trans_Ball);

	//�Ǘp�̐ݒ�
	const float WALL_WIDTH  = WIDTH;
	const float WALL_HEIGHT = 10.0f;

	Transform trans_Wall[2] = {};
	trans_Wall[0].SetPosition(0, 0, 0);						//��p
	trans_Wall[1].SetPosition(0, HEIGHT - WALL_HEIGHT, 0);	//���p

	//�Ǐ�
	pWall_T = new GameEngine::Rectangle(WALL_WIDTH, WALL_HEIGHT);
	pWall_T->SetUpTransform(trans_Wall[0]);

	//�ǉ�
	pWall_B = new GameEngine::Rectangle(WALL_WIDTH, WALL_HEIGHT);
	pWall_B->SetUpTransform(trans_Wall[1]);

	/////////////////////////////////////////////////////////////////////
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
	delete pFPSManager;
	delete pBackBuff;
	delete pInput;
	DX12::Destroy();
	mWindow.QuitApp();
}

void Game::InputActions()
{
	mKey_W = pInput->GetKey(DIK_W);
	mKey_S = pInput->GetKey(DIK_S);
	mKey_A = pInput->GetKey(DIK_A);
	mKey_D = pInput->GetKey(DIK_D);
}

void Game::Update()
{
	auto deltaTime = pFPSManager->GetDeltaTime();

	if		(mKey_W) pBall->mTransform.position.y -= SPEED * deltaTime;
	else if (mKey_S) pBall->mTransform.position.y += SPEED * deltaTime;
	else if	(mKey_A) pBall->mTransform.position.x -= SPEED * deltaTime;
	else if (mKey_D) pBall->mTransform.position.x += SPEED * deltaTime;

	pBall->Update();
}

void Game::Output()
{
	////////////////////////////////////////////////////////////////////
	//�`�揀��
	pDX12->EnterDrawing();

	//��ʃN���A�F
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	//�o�b�N�o�b�t�@�[�̏���
	pBackBuff->OpenBackBuffer(clearColor);
	////////////////////////////////////////////////////////////////////

	//�`��
	pBall->Draw();
	pWall_T->Draw();
	pWall_B->Draw();

	////////////////////////////////////////////////////////////////////
	//�o�b�N�o�b�t�@�[�̕`��I������
	pBackBuff->CloseBackBuffer();

	//�`��I��
	pDX12->ExitDrawing();
	////////////////////////////////////////////////////////////////////
}
