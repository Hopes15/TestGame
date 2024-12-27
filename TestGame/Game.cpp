#include "Game.h"

void Game::Initialize()
{
	const UINT WIDTH  = 640;
	const UINT HEIGHT = 480;

	//�E�B���h�E�쐬
	mWindow.SetUpWindow(WIDTH, HEIGHT, L"TestGame");

	//DX12�G���W�����쐬
	DX12::Create(WIDTH, HEIGHT, mWindow.GetWindowHandler());
	pDX12 = DX12::GetInstance();

	//�o�b�N�o�b�t�@�[����
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
	//�`�揀��
	pDX12->EnterDrawing();

	//��ʃN���A�F
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	//�o�b�N�o�b�t�@�[�̏���
	pBackBuff->OpenBackBuffer(clearColor);
}

void Game::Update()
{
}

void Game::Output()
{
	//�o�b�N�o�b�t�@�[�̕`��I������
	pBackBuff->CloseBackBuffer();

	//�`��I��
	pDX12->ExitDrawing();
}
