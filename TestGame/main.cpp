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

	////ウィンドウ作成
	//Window window;
	//window.SetUpWindow(WIDTH, HEIGHT, L"TestGame");

	////DX12エンジンを作成
	//DX12 dx12(WIDTH, HEIGHT, window.GetWindowHandler());

	////三角形作成
	//Triangle triangle(dx12.GetDevice());

	////画面クリア色
	//const float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	////ゲームループ
	//bool isActive = true;
	//while (isActive)
	//{
	//	//TODO:FPS制限をできるようにする(mmsystem.hを用いたSleepによるフレーム管理)

	//	/////////////////////////////////////////////////////////////////
	//	isActive = window.GameLoop();

	//	//描画準備
	//	dx12.EnterDrawing();
	//	//バックバッファーの準備
	//	dx12.OpenBackBuffer(clearColor);
	//	/////////////////////////////////////////////////////////////////

	//	//更新
	//	triangle.Update();

	//	//描画
	//	triangle.Draw(dx12.GetCmdList());

	//	/////////////////////////////////////////////////////////////////
	//	//バックバッファーの描画終了処理
	//	dx12.CloseBackBuffer();
	//	//描画終了
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