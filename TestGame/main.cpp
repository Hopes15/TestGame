#include <Windows.h>
#include "Game.h"

#ifdef _DEBUG
int main()
{
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif
	
	Game testGame;
	testGame.Initialize();
	testGame.RunLoop();
	testGame.Quit();

	return 0;
}