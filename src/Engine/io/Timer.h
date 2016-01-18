////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2012-11-14 23:19:02
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_20121114231902_H_
#define	_Tian_20121114231902_H_

#include "Base/Config.h"

namespace panda
{
	/*
	*
	*/
	class CTimer
	{
	public:
		CTimer();

		void	BeginTickTime();
		double	EndTickTime();
		s64		GetTickTime();
	protected:
		s64 begin_time;
		s64 end_time;
		s64 time_fre;
		double time_elapsed;
	};
}

#endif _Tian_20121114231902_H_