#include <Windows.h>
#include "Game.h"

#ifdef _DEBUG
int main()
{
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif
	//TEST
	{
		//const UINT WIDTH  = 1280;
	//const UINT HEIGHT = 720;

	////�E�B���h�E�쐬
	//Window window;
	//window.SetUpWindow(WIDTH, HEIGHT, L"TestGame");

	////DX12�G���W�����쐬
	//DX12 dx12(WIDTH, HEIGHT, window.GetWindowHandler());

	////�O�p�`�쐬
	//Triangle triangle(dx12.GetDevice());

	////��ʃN���A�F
	//const float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	////�Q�[�����[�v
	//bool isActive = true;
	//while (isActive)
	//{
	//	//TODO:FPS�������ł���悤�ɂ���(mmsystem.h��p����Sleep�ɂ��t���[���Ǘ�)

	//	/////////////////////////////////////////////////////////////////
	//	isActive = window.GameLoop();

	//	//�`�揀��
	//	dx12.EnterDrawing();
	//	//�o�b�N�o�b�t�@�[�̏���
	//	dx12.OpenBackBuffer(clearColor);
	//	/////////////////////////////////////////////////////////////////

	//	//�X�V
	//	triangle.Update();

	//	//�`��
	//	triangle.Draw(dx12.GetCmdList());

	//	/////////////////////////////////////////////////////////////////
	//	//�o�b�N�o�b�t�@�[�̕`��I������
	//	dx12.CloseBackBuffer();
	//	//�`��I��
	//	dx12.ExitDrawing();
	//	/////////////////////////////////////////////////////////////////
	//}

	//window.QuitApp();
	}
	
	Game testGame;
	testGame.Initialize();
	testGame.RunLoop();
	testGame.Quit();

	return 0;
}