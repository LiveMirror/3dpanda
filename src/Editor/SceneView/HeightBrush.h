//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/16 17:08:33_
// ����:  
//

#ifndef _HEIGHTBRUSH_2014516170833_
#define _HEIGHTBRUSH_2014516170833_

#include "IBrush.h"

namespace editor
{
	class HeightBrush:public IBrush
	{
	public:
		HeightBrush(void);

		virtual	void		OnPaint(f32 x, f32 y);
	};
}

#endif // _HEIGHTBRUSH_2014516170833_