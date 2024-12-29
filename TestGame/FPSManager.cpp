#include "FPSManager.h"

FPSManager::FPSManager(const UINT TARGET_FPS) : FRAME_TIME/*seconds*/(1.0f / TARGET_FPS)
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
	mDeltaTime = static_cast<float>(mTime_Current.QuadPart - mTime_Previous.QuadPart) / static_cast<float>(mTime_Freq.QuadPart);
	
	if (mDeltaTime < FRAME_TIME)
	{
		//��~���Ԃ̌v�Z
		DWORD time_Sleep = static_cast<DWORD>((FRAME_TIME - mDeltaTime) * 1000);

		//Sleep
		timeBeginPeriod(1);
		Sleep(time_Sleep);
		timeEndPeriod(1);
	}

	//FPS�̌v�Z
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
