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

	//�o�b�N�o�b�t�@�[����
	pBackBuff = new BackBuffer();

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
}

void Game::RunLoop()
{
	bool isActive = true;
	while (isActive)
	{
		isActive = mWindow.GetMSG();

		Input();
		Update();
		Output();

		pFPSManager->CalcFPS();
		pFPSManager->OutputFPS();
	}
}

void Game::Quit()
{
	delete pFPSManager;
	delete pBackBuff;
	DX12::Destroy();
	mWindow.QuitApp();
}

void Game::Input()
{

}

void Game::Update()
{
	auto deltaTime = pFPSManager->GetDeltaTime();

	pBall->mTransform.position.x += 100.0f * deltaTime;
	pBall->mTransform.position.y += 100.0f * deltaTime;
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
