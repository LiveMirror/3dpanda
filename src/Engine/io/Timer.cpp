#include "Timer.h"

namespace panda
{
	CTimer::CTimer()
	{
		LARGE_INTEGER litmp;
		QueryPerformanceFrequency(&litmp);
		time_fre = litmp.QuadPart;	//CPU ÆµÂÊ
	}

	void CTimer::BeginTickTime()
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&begin_time);
	}

	double CTimer::EndTickTime()
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&end_time);
		time_elapsed = (double)(end_time - begin_time) / time_fre;
		return time_elapsed;
	}

	s64 CTimer::GetTickTime()
	{
		LONGLONG passTime;
		QueryPerformanceCounter((LARGE_INTEGER *)&passTime);
		return passTime * 1000 / time_fre;
	}
}