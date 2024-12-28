#include "Game.h"

void Game::Initialize()
{
	const UINT WIDTH  = 640;
	const UINT HEIGHT = 480;

	const float BALL_WIDTH  = 5.0f;
	const float BALL_HEIGHT = 5.0f;

	//�E�B���h�E�쐬
	mWindow.SetUpWindow(WIDTH, HEIGHT, L"TestGame");

	//DX12�G���W�����쐬
	DX12::Create(WIDTH, HEIGHT, mWindow.GetWindowHandler());
	pDX12 = DX12::GetInstance();

	//�o�b�N�o�b�t�@�[����
	pBackBuff = new BackBuffer();

	//�{�[���p�̏����l�ݒ�
	Transform transform = {};
	auto width  = (WIDTH  / 2) - (BALL_WIDTH  / 2);
	auto height = (HEIGHT / 2) - (BALL_HEIGHT / 2);
	transform.SetPosition(width, height, 0);
	transform.SetScale(10, 20, 0);

	//�{�[��
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
	//�`�揀��
	pDX12->EnterDrawing();

	//��ʃN���A�F
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	//�o�b�N�o�b�t�@�[�̏���
	pBackBuff->OpenBackBuffer(clearColor);
	////////////////////////////////////////////////////////////////////

	//�`��
	pRectangle->Draw();

	////////////////////////////////////////////////////////////////////
	//�o�b�N�o�b�t�@�[�̕`��I������
	pBackBuff->CloseBackBuffer();

	//�`��I��
	pDX12->ExitDrawing();
	////////////////////////////////////////////////////////////////////
}
