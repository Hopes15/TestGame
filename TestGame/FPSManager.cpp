#include "FPSManager.h"

FPSManager::FPSManager(const float TARGET_FPS) : FRAME_TIME_S(1.0f / TARGET_FPS)
{
	//����������
	QueryPerformanceFrequency(&mTime_Freq);
	QueryPerformanceCounter(&mTime_Previous);	//���ݎ��Ԏ擾
}

void FPSManager::CalcFPS()
{
	QueryPerformanceCounter(&mTime_Current);	//���ݎ��Ԏ擾

	//1�t���[���̌o�ߎ��Ԃ��v�Z
	//mFrameTime = (���̎��� - �O�̎���) / ���g��
	mDeltaTime_s = static_cast<float>(mTime_Current.QuadPart - mTime_Previous.QuadPart) / static_cast<float>(mTime_Freq.QuadPart);
	
	if (mDeltaTime_s < FRAME_TIME_S)
	{
		//��~���Ԃ̌v�Z
		DWORD time_Sleep_ms = static_cast<DWORD>((FRAME_TIME_S - mDeltaTime_s) * 1000);

		//Sleep
		timeBeginPeriod(1);
		Sleep(time_Sleep_ms);
		timeEndPeriod(1);
	}

	//FPS�̌v�Z
	mFPS = 1.0f / mDeltaTime_s;

	mTime_Previous = mTime_Current;
}

FPSManager::~FPSManager()
{
}

void FPSManager::OutputFPS()
{
#ifdef _DEBUG
	std::cout << mFPS << " FPS" << std::endl;
#endif
}
