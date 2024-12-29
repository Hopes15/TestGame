#include "FPSManager.h"

FPSManager::FPSManager(const UINT TARGET_FPS) : FRAME_TIME/*seconds*/(1.0f / TARGET_FPS)
{
	//初期化処理
	QueryPerformanceFrequency(&mTime_Freq);
	QueryPerformanceCounter(&mTime_Previous);	//現在時間取得
}

void FPSManager::CalcFPS()
{
	QueryPerformanceCounter(&mTime_Current);	//現在時間取得

	//1フレームの経過時間を計算
	//mFrameTime = (今の時間 - 前の時間) / 周波数
	mDeltaTime = static_cast<float>(mTime_Current.QuadPart - mTime_Previous.QuadPart) / static_cast<float>(mTime_Freq.QuadPart);
	
	if (mDeltaTime < FRAME_TIME)
	{
		//停止時間の計算
		DWORD time_Sleep = static_cast<DWORD>((FRAME_TIME - mDeltaTime) * 1000);

		//Sleep
		timeBeginPeriod(1);
		Sleep(time_Sleep);
		timeEndPeriod(1);
	}

	//FPSの計算
	mFPS = 1.0f / mDeltaTime;

	mTime_Previous = mTime_Current;
}

FPSManager::~FPSManager()
{
}

void FPSManager::OutputFPS()
{
	std::cout << mFPS << " FPS" << std::endl;
}
