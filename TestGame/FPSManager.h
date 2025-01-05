#pragma once
#ifdef _DEBUG
#include <iostream>
#endif

#include "Windows.h"

//mmSystem
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

class FPSManager
{
public:
	/// <summary>
	/// FPSManager��������
	/// </summary>
	/// <param name="TARGET_FPS">�ڕW�Ƃ���FPS</param>
	FPSManager(const float TARGET_FPS);

	/// <summary>
	/// FPS���v�Z
	/// </summary>
	void CalcFPS();

	/// <summary>
	/// FPS���R���\�[���ɏo��
	/// </summary>
	void OutputFPS();

	/// <summary>
	/// DeltaTime��Ԃ�
	/// </summary>
	/// <returns>float DeltaTime</returns>
	inline float GetDeltaTime() { return mDeltaTime_s; }

	~FPSManager();

private:
	const float FRAME_TIME_S;
		  float mDeltaTime_s	 = 0.0f;
		  float mFPS			 = 0.0f;

	LARGE_INTEGER mTime_Previous = {};
	LARGE_INTEGER mTime_Current	 = {};
	LARGE_INTEGER mTime_Freq	 = {};
};

